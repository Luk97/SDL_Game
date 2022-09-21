#pragma once
#include <string>
#include <vector>

struct Layer {
    Layer(std::string layerID, std::string grp, std::vector<std::vector<int>> layerData):
        id(layerID), group(grp), data(layerData) {}

    std::string id;
    std::string group;
    std::vector<std::vector<int>> data;
};


struct Map {
    Map(int mapRows, int mapCols, int mapTilesize, std::vector<Layer*> mapLayers):
        rows(mapRows), cols(mapCols), tilesize(mapTilesize), layers(mapLayers) {}

        int rows;
        int cols;
        int tilesize;

        std::vector<Layer*> layers;
};
