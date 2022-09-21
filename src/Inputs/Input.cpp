#include "Input.h"
#include "Engine.h"
#include "CollisionManager.h"

#include <iostream>

Input* Input::instance = nullptr;

void Input::listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                Engine::getInstance()->quit();
                break;
            case SDL_KEYDOWN:
                keyStates = SDL_GetKeyboardState(nullptr);

                break;
            case SDL_KEYUP:
                keyStates = SDL_GetKeyboardState(nullptr);

                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_C:
                        CollisionManager::getInstance()->setDrawColliderOption();
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        Engine::getInstance()->quit();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

bool Input::isPressed(SDL_Scancode key) {
    return (keyStates[key] == 1);
}

