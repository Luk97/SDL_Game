#pragma once
#include "SDL.h"

class Input
{
    public:
        inline static Input* getInstance() {return instance = (instance != nullptr) ? instance : new Input();}

        void listen();
        bool isPressed(SDL_Scancode key);

    private:
        Input() {keyStates = SDL_GetKeyboardState(nullptr);}
        static Input* instance;

        const Uint8* keyStates;
};
