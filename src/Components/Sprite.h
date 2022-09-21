#pragma once
#include <string>
#include "SDL.h"
#include "Vector2D.h"
#include "TextureManager.h"

struct Sprite
{
    Sprite(std::string texID, SDL_Rect srcR, Vector2D* pos, float sc) {
        textureID = texID;
        srcRect = srcR;
        dstRect = {(int)pos->x, (int)pos->y, (int)(srcRect.w * sc), (int)(srcRect.h * sc)};
        scale = sc;
        position = pos;
    }

    void draw() {
        dstRect.x = position->x;
        dstRect.y = position->y;

        TextureManager::getInstance()->draw(textureID, srcRect, dstRect);
    }

    std::string textureID;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    float scale;
    Vector2D* position;
};
