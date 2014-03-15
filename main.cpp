#include "stdafx.h"
#include "Game.h"

Game game;
int scale = 128;

int main()
{
    Game::Status state = Game::Local;
    while(state != Game::Quit)
    {
        if(state == Game::Local)
            state = game.local();
        else if(state == Game::Client)
            state = game.client();
        else if(state == Game::Server)
            state = game.server();
    }
    std::cout << "Done\n\n";
    return 0;
}
