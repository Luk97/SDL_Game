#include "XmlParser.h"
#include "tinyxml.h"
#include "Engine.h"
#include "TextureManager.h"
#include "MapManager.h"
#include "AnimationManager.h"
#include "EntityManager.h"
#include <iostream>
#include <sstream>

XmlParser* XmlParser::instance = nullptr;

void parseMap(TiXmlElement* e);
void parseTileset(TiXmlElement* e);
void parseLayer(TiXmlElement* e);
void parseEntities(TiXmlElement* e);

void XmlParser::parse(std::string source) {
    TiXmlDocument doc;
    doc.LoadFile(source.c_str());

    if (doc.Error()) {
        std::cout << "ERROR: Failed to load: " << source << std::endl;
        return;
    }

    TiXmlElement* root = doc.RootElement();

    parseMap(root);

    std::vector<Tileset*> tilesets;
    std::vector<Layer*> layers;

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {

        if (e->Value() == std::string("tileset"))
            parseTileset(e);

        if (e->Value() == std::string("layer"))
            parseLayer(e);

        if (e->Value() == std::string("objectgroup") && e->Attribute("name") == std::string("entity"))
            parseEntities(e);
    }
}

void parseMap(TiXmlElement* e) {
    int rows, cols, tilesize;
    e->Attribute("width", &cols);
    e->Attribute("height", &rows);
    e->Attribute("tilewidth", &tilesize);
    MapManager::getInstance()->setMap(rows, cols, tilesize);
}

void parseTileset(TiXmlElement* e) {
    // parse values of tileset
    std::string name = e->Attribute("name");
    int firstID, lastID, tilecount, tilesize, rows, cols;
    e->Attribute("firstgid", &firstID);
    e->Attribute("tilecount", &tilecount);
    lastID = (firstID + tilecount) - 1;
    e->Attribute("columns", &cols);
    rows = tilecount / cols;
    e->Attribute("tilewidth", &tilesize);

    TextureManager::getInstance()->addTileset(name, firstID, lastID, tilecount, tilesize, rows, cols);
}

void parseLayer(TiXmlElement* e) {
    std::string id = e->Attribute("name");
    std::string group = e->Attribute("class");

    // get size temporarily for iterating through data
    int rows, cols;
    e->Attribute("width", &cols);
    e->Attribute("height", &rows);

    std::vector<std::vector<int>> data(rows, std::vector<int>(cols, 0));
    for (TiXmlElement* e2 = e->FirstChildElement(); e2 != nullptr; e2 = e2->NextSiblingElement()) {

        // parse csv matrix into data
        if (e2->Value() == std::string("data")) {
            std::istringstream stream(e2->GetText());
            std::string buffer;

            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    std::getline(stream, buffer, ',');
                    std::stringstream convertor(buffer);
                    convertor >> data[row][col];

                    if (!stream.good())
                        break;
                }
            }
        }
    }
    MapManager::getInstance()->addLayer(id, group, data);
}

void parseEntities(TiXmlElement* e) {
    for (TiXmlElement* entity = e->FirstChildElement(); entity != nullptr; entity = entity->NextSiblingElement()) {
        if (entity->Value() == std::string("object")) {
            int id;
            entity->Attribute("id", &id);

            std::string classname;
            classname = entity->Attribute("class");

            int gid;
            entity->Attribute("gid", &gid);
            Tileset* tileset = TextureManager::getInstance()->getTilesetByID(gid);
            gid += tileset->tilecount - tileset->lastID - 1;
            int srcX = gid / tileset->cols;
            int srcY = gid / tileset->cols;

            std::string texID = tileset->name;

            int xpos, ypos, width, height;
            entity->Attribute("x", &xpos);
            entity->Attribute("y", &ypos);
            entity->Attribute("width", &width);
            entity->Attribute("height", &height);

            // Find property values of object
            double speed, scale;
            for (TiXmlElement* props = entity->FirstChildElement(); props != nullptr; props = props->NextSiblingElement()) {
                if (props->Value() == std::string("properties")) {
                    for (TiXmlElement* prop = props->FirstChildElement(); prop != nullptr; prop = prop->NextSiblingElement()) {
                        if (prop->Attribute("name") == std::string("speed"))
                            prop->Attribute("value", &speed);
                        if (prop->Attribute("name") == std::string("scale"))
                            prop->Attribute("value", &scale);
                    }
                }
            }

            // find collider of object
            TiXmlElement* colliderlayer = e->NextSiblingElement();
            if (colliderlayer->Attribute("name") != std::string("entity_collision")) {
                std::cout << "ERROR: failed to load collider properties" << std::endl;
                return;
            }

            int xcol, ycol, wcol, hcol;
            std::string colliderTextureID;
            for (TiXmlElement* collider = colliderlayer->FirstChildElement(); collider != nullptr; collider = collider->NextSiblingElement()) {
                for (TiXmlElement* colliderProps = collider->FirstChildElement(); colliderProps != nullptr; colliderProps = colliderProps->NextSiblingElement()) {
                    if (colliderProps->Value() == std::string("properties")) {
                        int tmpVal;
                        colliderProps->FirstChildElement()->Attribute("value", &tmpVal);

                        if (tmpVal == id) {
                            collider->Attribute("gid", &gid);
                            Tileset* tmp = TextureManager::getInstance()->getTilesetByID(gid);
                            colliderTextureID = tmp->name;
                            collider->Attribute("x", &xcol);
                            collider->Attribute("y", &ycol);
                            collider->Attribute("width", &wcol);
                            collider->Attribute("height", &hcol);
                            break;
                        }
                    }
                }
            }

            Properties props = {
                .xpos = xpos,
                .ypos = ypos - height,
                .speed = (float)speed,
                .texID = texID,
                .srcRect = {srcX, srcY, width, height},
                .scale = (float)scale,
                .xcol = xcol,
                .ycol = ycol - hcol,
                .wcol = wcol,
                .hcol = hcol,
                .texcol = colliderTextureID
            };
            EntityManager::getInstance()->addEntity(classname, &props);
        }
    }
}
















