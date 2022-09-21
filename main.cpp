#include "Engine.h"

int main(int argc, char** argv)
{
    Engine* e = Engine::getInstance();
    e->init();

    while (e->running()) {

        e->events();

        e->update();

        e->render();

        e->tick();
    }
    e->clean();
    return 0;
}
