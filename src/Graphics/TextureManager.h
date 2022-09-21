#pragma once
#include <string>
#include <map>
#include "Tileset.h"

class TextureManager {
public:
    inline static TextureManager* getInstance() {return instance = (instance != nullptr) ? instance : new TextureManager();}

    void addTileset(std::string name, int firstID, int lastID, int tilecount, int tilesize, int rows, int cols);
    void draw(std::string id, SDL_Rect srcRect, SDL_Rect dstRect);
    Tileset* getTilesetByID(int gid);
    void printInfo();
    void clean();

    // TODO
    bool containsID(std::string id);



private:
    TextureManager() {}
    static TextureManager* instance;

    std::map<std::string, Tileset*> tilesets;
};
