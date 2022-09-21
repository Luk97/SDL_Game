#pragma once
#include "Player.h"
#include <string>
#include <functional>
#include <map>
#include <vector>
#include "tinyxml.h"
#include "Entity.h"


class EntityManager {
public:
    inline static EntityManager* getInstance() {return instance = (instance != nullptr) ? instance : new EntityManager();}
    inline Player* getPlayer() {return (Player*)entities["PLAYER"].at(0);}

    void addEntity(std::string type, Properties* props);
    void update(float dt);
    void render();
    void printInfo();
    void clean();

private:
    EntityManager() {}
    static EntityManager* instance;

    // layer 0: "PLAYER"
    std::map<std::string, std::vector<Entity*>> entities;
};
