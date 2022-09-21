#pragma once

#include "Components.h"



struct Properties {
    int xpos;
    int ypos;
    float speed;
    std::string texID;
    SDL_Rect srcRect;
    float scale;
    int xcol, ycol, wcol, hcol;
    std::string texcol;
};

class Entity
{
    public:
        Entity(Properties* props) {}

        virtual void update(float dt) = 0;
        virtual void render() = 0;
        virtual void clean() = 0;
};
