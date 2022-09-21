#include "Timer.h"
#include "SDL.h"

#include <iostream>

Timer* Timer::instance = nullptr;

void Timer::tick() {
    deltaTime = (SDL_GetTicks() - lastTime) * (TARGET_FPS / 1000.0f);

    if (deltaTime > MAX_DELTATIME)
        deltaTime = MAX_DELTATIME;

    lastTime = SDL_GetTicks();
}
