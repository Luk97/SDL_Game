#include "Engine.h"
#include "Input.h"
#include "XmlParser.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "Vector2D.h"
#include <iostream>
#include "MapManager.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Player.h"

Engine* Engine::instance = nullptr;

void Engine::init() {

    // SDL Initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "ERROR: " << SDL_GetError() <<  std::endl;
        return;
    }

    // SDL Image Initialization
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "ERROR: " << IMG_GetError() << std::endl;
        return;
    }

    // Window creation
    window = SDL_CreateWindow("Fantasy Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == nullptr) {
        std::cout << "ERROR: " << SDL_GetError() << std::endl;
        return;
    }

    // Renderer creation
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "ERROR: " << SDL_GetError() << std::endl;
        return;
    }

    isRunning = true;

    // Load map
    XmlParser::getInstance()->parse("assets/maps/map.tmx");

    TextureManager::getInstance()->printInfo();
    MapManager::getInstance()->printInfo();
    EntityManager::getInstance()->printInfo();

    Camera::getInstance()->setTarget(EntityManager::getInstance()->getPlayer()->getTransform()->position,
                                     &EntityManager::getInstance()->getPlayer()->getSprite()->dstRect.w,
                                     &EntityManager::getInstance()->getPlayer()->getSprite()->dstRect.h);
}


void Engine::events() {
    Input::getInstance()->listen();
}


void Engine::update() {
    float dt = Timer::getInstance()->getDeltaTime();
    EntityManager::getInstance()->update(dt);
    Camera::getInstance()->update();
}


void Engine::render() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);

    MapManager::getInstance()->renderMap();
    EntityManager::getInstance()->render();

    SDL_RenderPresent(renderer);
}

void Engine::quit() {
    isRunning = false;
}


void Engine::clean() {
    EntityManager::getInstance()->clean();
    MapManager::getInstance()->clean();
    TextureManager::getInstance()->clean();
    //AnimationManager::getInstance()->clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
