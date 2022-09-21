#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Timer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640

class Engine
{
    public:
        inline static Engine* getInstance() {return instance = (instance != nullptr) ? instance : new Engine();}
        inline bool running() {return isRunning;}

    public:
        void init();
        void events();
        void update();
        void render();
        void quit();
        void clean();

        inline void tick() {Timer::getInstance()->tick();}
        inline SDL_Renderer* getRenderer() {return renderer;}

    private:
        Engine() {}
        static Engine* instance;

    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;

};
