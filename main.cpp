#include "Controller.h"

int main(int argc, char **argv)
{
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    Uint32 start_time;
    Controller controller = Controller();
    controller.initializeSDL("BBTan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 800, SDL_WINDOW_SHOWN);

    while (!controller.isEndLoop())
    {
        if (controller.getNewGame())
        {
            controller.setNewGame(false);
            controller.initObjects();
        }
        start_time = SDL_GetTicks();
        controller.handleEvent();
        controller.update();

        controller.render();
        if (SDL_GetTicks() - start_time < frame_delay)
        {
            SDL_Delay(frame_delay - (SDL_GetTicks() - start_time));
        }
    }
    controller.close();
    return 0;
}
