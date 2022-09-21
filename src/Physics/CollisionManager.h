#pragma once
#include "SDL.h"

class CollisionManager
{
    public:
        inline static CollisionManager* getInstance() {return instance = (instance != nullptr) ? instance : new CollisionManager();}
        inline void setDrawColliderOption() {drawColliderOption = !drawColliderOption;}
        inline bool requestDrawColliderOption() {return drawColliderOption;}

        bool checkForMapCollision(SDL_Rect* collider);


    private:
        CollisionManager() {drawColliderOption = false;}
        static CollisionManager* instance;
        bool drawColliderOption;
};
