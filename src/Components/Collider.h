#pragma once
#include "SDL.h"
#include "Entity.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include <string>
#include <iostream>

struct Collider {
    Collider(std::string texcol, int xcol, int ycol, int w, int h, float scale, Vector2D* currPos, Vector2D* lastSavePos) {
        colliderTextureID = texcol;
        entityPosition = currPos;
        lastSafePosition = lastSavePos;

        colliderBox.w = w * scale;
        colliderBox.h = h * scale;
        xoffset = (xcol - currPos->x) * scale;
        yoffset = (ycol - currPos->y) * scale;
    }


    inline void update() {
        colliderBox.x = (int)entityPosition->x + xoffset;
        colliderBox.y = (int)entityPosition->y + yoffset;


        if (CollisionManager::getInstance()->checkForMapCollision(&colliderBox)) {
            entityPosition->x = lastSafePosition->x;
            entityPosition->y = lastSafePosition->y;
            colliderBox.x = (int)lastSafePosition->x + xoffset;
            colliderBox.y = (int)lastSafePosition->y + yoffset;
        }
    }

    inline void draw() {
        TextureManager::getInstance()->draw(colliderTextureID, {0, 0, 16, 16}, {colliderBox.x, colliderBox.y, colliderBox.w, colliderBox.h});
    }

    std::string colliderTextureID;
    int xoffset, yoffset;
    Vector2D* entityPosition;
    Vector2D* lastSafePosition;
    SDL_Rect colliderBox;
};
