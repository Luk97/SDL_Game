#include "MapManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Camera.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Input.h>


MapManager* MapManager::instance = nullptr;

void MapManager::addLayer(std::string id, std::string group, std::vector<std::vector<int>> data) {
    currentMap->layers.push_back(new Layer(id, group, data));
}

void MapManager::setMap(int row, int col, int tilesize) {
    currentMap = new Map(row, col, tilesize, std::vector<Layer*>());
}

Layer* MapManager::getCollisionlayer() {
    for (unsigned int i = 0; i < currentMap->layers.size(); i++)
        if (currentMap->layers[i]->group == std::string("collisionlayer"))
            return currentMap->layers[i];
    std::cout << "ERROR: Could not find collision layer" << std::endl;
    return nullptr;
}

int MapManager::getMapTilesize() {
    if (currentMap == nullptr) {
        std::cout << "ERROR: no map currently loaded" << std::endl;
        return -1;
    }
    return currentMap->tilesize;
}

// check if tile is visible in screen
bool inRange(int xpos, int ypos, int tilesize) {
    SDL_Rect cam = Camera::getInstance()->getViewbox();
    return xpos > cam.x - tilesize && xpos < cam.x + cam.w && ypos > cam.y - tilesize && ypos < cam.y + cam.h;
}


void MapManager::renderMap() {
    for (unsigned int layerIndex = 0; layerIndex < currentMap->layers.size(); layerIndex++) {
        for (int row = 0; row < currentMap->rows; row++) {
            for (int col = 0; col < currentMap->cols; col++) {

                if (currentMap->layers[layerIndex]->group == std::string("collisionlayer") && !CollisionManager::getInstance()->requestDrawColliderOption())
                    continue;

                int tileID = currentMap->layers[layerIndex]->data[row][col];

                if (tileID == 0 || !inRange(col * currentMap->tilesize, row * currentMap->tilesize, currentMap->tilesize))
                    continue;

                // find the tileset with tileID
                Tileset* tileset = TextureManager::getInstance()->getTilesetByID(tileID);

                tileID--;   // because tilesetID starts with 1 instead if 0

                int tilesetRow = tileID / tileset->cols;
                int tilesetCol = tileID % tileset->cols;
                int ts = tileset->tilesize;

                TextureManager::getInstance()->draw(tileset->name, {tilesetCol * ts, tilesetRow * ts, ts, ts}, {col * ts, row * ts, ts, ts});
            }
        }
    }
}


void MapManager::printInfo() {
    std::cout << "--------------------" << std::endl;
    std::cout << "INFO: MapManager" << std::endl;
    std::cout << "Size: " << currentMap->rows << "x" << currentMap->cols << std::endl;
    std::cout << "Layers: " << currentMap->layers.size() << std::endl;
    std::cout << "--------------------" << std::endl;
}


void MapManager::clean() {
    currentMap->layers.clear();
    currentMap = nullptr;
}
















