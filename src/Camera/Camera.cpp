#include "Camera.h"
#include "Util.h"
#include <iostream>

Camera* Camera::instance = nullptr;


void Camera::update() {
    if (target == nullptr)
        return;

    viewbox.x = Util::clamp(target->x - viewbox.w / 2 + *targetWidth, 0, viewbox.w);
    viewbox.y = Util::clamp(target->y - viewbox.h / 2 + *targetHeight, 0, viewbox.h);
}
