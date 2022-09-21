#pragma once
#include "SDL.h"
#include "Vector2D.h"
#include "Engine.h"

class Camera
{
    public:
        static inline Camera* getInstance() {return instance = (instance != nullptr) ? instance : new Camera();}

        inline void setTarget(Vector2D* t, int* tWidth, int* tHeight) {
            target = t;
            targetWidth = tWidth;
            targetHeight = tHeight;
        }
        inline SDL_Rect getViewbox() {return viewbox;}

        void update();

    private:
        Camera() {
            viewbox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            target = nullptr;
        }

        static Camera* instance;
        SDL_Rect viewbox;
        Vector2D* target;
        int* targetWidth;
        int* targetHeight;
};
