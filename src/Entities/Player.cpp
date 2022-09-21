#include "Player.h"
#include "Input.h"
#include "EntityManager.h"
#include <iostream>


Player::Player(Properties* props): Character(props) {
    transform = new Transform(props->xpos, props->ypos, props->speed);
    sprite = new Sprite(props->texID, props->srcRect, transform->position, props->scale);
    collider = new Collider(props->texcol, props->xcol, props->ycol, props->wcol, props->hcol, sprite->scale, transform->position, transform->lastSafePosition);
}


void Player::update(float dt) {
    transform->velocity->zero();

    if (Input::getInstance()->isPressed(SDL_SCANCODE_A)) {
        transform->velocity->x = -1;
    }
    if (Input::getInstance()->isPressed(SDL_SCANCODE_D)) {
        transform->velocity->x = 1;
    }
    if (Input::getInstance()->isPressed(SDL_SCANCODE_W)) {
        transform->velocity->y = -1;
    }
    if (Input::getInstance()->isPressed(SDL_SCANCODE_S)) {
        transform->velocity->y = 1;
    }

    transform->update(dt);
    collider->update();
}



void Player::render() {
    sprite->draw();
    if (CollisionManager::getInstance()->requestDrawColliderOption())
        collider->draw();
}

void Player::clean() {

}
