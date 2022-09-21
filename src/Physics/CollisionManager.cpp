#include "CollisionManager.h"
#include "MapManager.h"
#include "Camera.h"
#include "Util.h"

CollisionManager* CollisionManager::instance = nullptr;


bool CollisionManager::checkForMapCollision(SDL_Rect* collider) {

    Layer* layer = MapManager::getInstance()->getCollisionlayer();
    if (layer == nullptr)
        return false;




    int rowMax = layer->data.size();
    int colMax = layer->data[0].size();
    int tilesize = MapManager::getInstance()->getMapTilesize();

    if (tilesize == -1)
        return false;

    int row = Util::clamp(collider->y / tilesize, 0 ,rowMax);
    int col = Util::clamp(collider->x / tilesize, 0, colMax);
    if (layer->data[row][col] > 0)
        return true;

    col = Util::clamp((collider->x + collider->w) / tilesize, 0, colMax);
    if (layer->data[row][col] > 0)
        return true;

    row = Util::clamp((collider->y + collider->h) / tilesize, 0, rowMax);
    if (layer->data[row][col] > 0)
        return true;

    col = Util::clamp(collider->x / tilesize, 0, colMax);
    if (layer->data[row][col] > 0)
        return true;


    return false;
}
