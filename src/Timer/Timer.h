#pragma once

#define TARGET_FPS 60
#define MAX_DELTATIME 1.5f

class Timer
{
    public:
        inline static Timer* getInstance() {return instance = (instance != nullptr) ? instance : new Timer();}
        inline float getDeltaTime() {return deltaTime;}

        void tick();

    private:
        Timer() {}
        static Timer* instance;

    private:
        float deltaTime;
        float lastTime;
};
