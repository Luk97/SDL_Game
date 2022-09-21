#pragma once
#include <iostream>

class Vector2D
{
    public:
        float x, y;

        Vector2D(float xpos = 0, float ypos= 0): x(xpos), y(ypos) {}

        inline void zero() {x = 0; y = 0;}

        // addition
        inline Vector2D operator+(const Vector2D& v2) const {
            return Vector2D(x + v2.x, y + v2.y);
        }

        // subtraction
        inline Vector2D operator-(const Vector2D& v2) const {
            return Vector2D(x - v2.x, y - v2.y);
        }

        // multiplication
        inline Vector2D operator*(const float scalar) const {
            return Vector2D(x * scalar, y * scalar);
        }

        // Log
        void log(std::string msg = "") {
            std::cout << msg << "(X Y) = (" << x << " " << y << ")" << std::endl;
        }
};
