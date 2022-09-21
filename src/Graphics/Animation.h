#pragma once
#include "Vector2D.h"
#include "SDL.h"
#include "TextureManager.h"
#include <string>
#include <vector>

class Animation
{
    public:
        Animation(std::string animID, int f, int s, int w, int h, std::vector<std::string> texIDs, bool looping = false) {
            id = animID;
            frames = f;
            speed = s;
            width = w;
            height = h;
            textureIDs = texIDs;
            isLooping = looping;
            hasEnded = false;
            currFrame = 0;
        }

        inline void update() {
            if (isLooping || !hasEnded)
                currFrame = (SDL_GetTicks() / speed) % frames;

            if (!isLooping && currFrame == frames - 1)
                hasEnded = true;
        }

        inline void draw(Vector2D* pos, int scale) {
             //TextureManager::getInstance()->draw(textureIDs[currFrame], 0, 0, width, height, (int)pos->x, (int)pos->y, width, height, scale);
        }

        inline std::string getID() {return id;}

    private:
        bool isLooping;
        bool hasEnded;
        int currFrame;

        std::string id;
        int frames;
        int speed;
        int width;
        int height;
        std::vector<std::string> textureIDs;

        friend class AnimationManager;
};
