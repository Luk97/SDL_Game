#include "AnimationManager.h"
#include "TextureManager.h"
#include <iostream>
#include "tinyxml.h"

AnimationManager* AnimationManager::instance = nullptr;


void AnimationManager::clean() {
    animations.clear();
}


void AnimationManager::printInfo() {
    std::cout << "INFO: #Loaded Animations: " << animations.size() << std::endl;
}
