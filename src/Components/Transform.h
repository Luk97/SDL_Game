#pragma once
#include "Vector2D.h"
#include <math.h>

struct Transform
{
    Transform(int xpos, int ypos, float s) {
        position = new Vector2D(xpos, ypos);
        lastSafePosition = new Vector2D(xpos, ypos);
        velocity = new Vector2D();
        speed = s;
    }

    inline void update(float dt) {
        float len = sqrt(velocity->x * velocity->x + velocity->y * velocity->y);
        if (len != 0) {
            velocity->x /= len;
            velocity->y /= len;
        }

        lastSafePosition->x = position->x;
        lastSafePosition->y = position->y;
        position->x += velocity->x * speed * dt;
        position->y += velocity->y * speed * dt;
    }

    Vector2D* position;
    Vector2D* lastSafePosition;
    Vector2D* velocity;
    float speed;
};
