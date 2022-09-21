#pragma once
#include <string>
#include "SDL.h"

struct Tileset {
    Tileset(std::string name, int fID, int lID, int tc, int ts, int r, int c, SDL_Texture* tex = nullptr):
        name(name), firstID(fID), lastID(lID), tilecount(tc), tilesize(ts), rows(r), cols(c), texture(tex) {}

    std::string name;
    int firstID;
    int lastID;
    int tilecount;
    int tilesize;
    int rows;
    int cols;
    SDL_Texture* texture;
};
