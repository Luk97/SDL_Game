#pragma once
#include "Animation.h"
#include <string>
#include <map>

class AnimationManager
{
    public:
        inline static AnimationManager* getInstance() {return instance = (instance != nullptr) ? instance : new AnimationManager();}

        inline void addAnimation(Animation* a) {animations[a->id] = a;}
        inline Animation* play(std::string id) {return animations[id];}
        void clean();
        void printInfo();

    private:
        AnimationManager() {}
        static AnimationManager* instance;

    private:
        std::map<std::string, Animation*> animations;
};
