#include "TextureManager.h"
#include <iostream>
#include "SDL.h"
#include "Engine.h"
#include "Camera.h"


TextureManager* TextureManager::instance = nullptr;

void TextureManager::addTileset(std::string name, int firstID, int lastID, int tilecount, int tilesize, int rows, int cols) {
    SDL_Surface* surface = IMG_Load(("assets/tilesets/" + name + ".png").c_str());
    if (surface == nullptr) {
        std::cout << "ERROR: Failed to load texture: " << name << ".png" << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), surface);
    if (texture == nullptr) {
        std::cout << "ERROR: Failed to create Texture from surface: " << name << ".png" << std::endl;
        return;
    }
    tilesets[name] = new Tileset(name, firstID, lastID, tilecount, tilesize, rows, cols, texture);
}


void TextureManager::draw(std::string id, SDL_Rect srcRect, SDL_Rect dstRect) {
    SDL_Rect cam = Camera::getInstance()->getViewbox();
    dstRect.x -= cam.x;
    dstRect.y -= cam.y;
    SDL_RenderCopy(Engine::getInstance()->getRenderer(), tilesets[id]->texture, &srcRect, &dstRect);
}

Tileset* TextureManager::getTilesetByID(int gid) {
    std::map<std::string, Tileset*>::iterator it;
    for (it = tilesets.begin(); it != tilesets.end(); it++)
        if (it->second->firstID <= gid && it->second->lastID >= gid)
            return it->second;

    std::cout << "ERROR: Could not find requested gid: " << gid << std::endl;
    return nullptr;
}

bool TextureManager::containsID(std::string id) {
    std::map<std::string, Tileset*>::iterator it;
    it = tilesets.find(id);
    return (it != tilesets.end());
}

void TextureManager::printInfo() {
    std::cout << "--------------------" << std::endl;
    std::cout << "INFO: TextureManager" << std::endl;
    std::cout << "Loaded Tilesets: " << tilesets.size() << std::endl;
    std::cout << "--------------------" << std::endl;
}

void TextureManager::clean() {

}



