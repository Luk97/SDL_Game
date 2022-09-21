#include "EntityManager.h"
#include <iostream>

EntityManager* EntityManager::instance = nullptr;


void EntityManager::addEntity(std::string type, Properties* props) {
    if (type == std::string("PLAYER"))
        entities[type].push_back(new Player(props));
}

void EntityManager::update(float dt) {
    std::map<std::string, std::vector<Entity*>>::iterator it;
    for (it = entities.begin(); it != entities.end(); it++)
        for (Entity* e : it->second)
            e->update(dt);
}

void EntityManager::render() {
    std::map<std::string, std::vector<Entity*>>::iterator it;
    for (it = entities.begin(); it != entities.end(); it++)
        for (Entity* e : it->second)
            e->render();
}

void EntityManager::printInfo() {
    std::cout << "--------------------" << std::endl;
    std::cout << "INFO: EntityManager" << std::endl;
    std::map<std::string, std::vector<Entity*>>::iterator it;
    for (it = entities.begin(); it != entities.end(); it++)
        std::cout << it->first << ": " << it->second.size() << std::endl;
    std::cout << "--------------------" << std::endl;
}

void EntityManager::clean() {

}




