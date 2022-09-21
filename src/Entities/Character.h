#pragma once
#include "Entity.h"
#include "Animation.h"


class Character: public Entity
{
    public:
        Character(Properties* props): Entity(props) {}

        virtual void update(float dt) = 0;
        virtual void render() = 0;
        virtual void clean() = 0;
};
