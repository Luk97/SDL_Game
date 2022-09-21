#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Map.h"

class MapManager {
public:
    inline static MapManager* getInstance() {return instance = (instance != nullptr) ? instance : new MapManager();}

    void addLayer(std::string id, std::string group, std::vector<std::vector<int>> data);
    void setMap(int row, int col, int tilesize);
    Layer* getCollisionlayer();
    int getMapTilesize();
    void renderMap();
    void printInfo();
    void clean();

private:
    MapManager() {}
    static MapManager* instance;
    Map* currentMap;
};
