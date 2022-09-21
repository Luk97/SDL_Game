#pragma once
#include "Character.h"



class Player: public Character {
public:
    Player(Properties* props);

    virtual void update(float dt);
    virtual void render();
    virtual void clean();

    inline Transform* getTransform() {return transform;}
    inline Sprite* getSprite() {return sprite;}

private:
    Transform* transform;
    Sprite* sprite;
    Collider* collider;
};
