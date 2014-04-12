#include "Game.h"

int main (int argc, char **argv)
{
    try
    {
        Game    game;
        return game.run();
    }
    catch (Error error)
    {
        error.ShowError();
    }
    catch (...)
    {
        std::cerr << "Unknow Error" << std::endl;
    }
    // il y a eu un problème , on quitte donc la SDL
    SDL_Quit();
    return EXIT_FAILURE;
}
