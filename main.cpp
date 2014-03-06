#include <stdafx.h>
#include <Game/Game.h>

//sf::ContextSettings settings = {4};
Game game;
int scale = 128;

///MOVE THIS TO AN EXAMPLE FILE
/**
class Bob
{
public:
    void destroy(Bob* p) {cout << "\nDestroyed";}
};
void deleter(Bob* p)
{
    cout << "\nWorks";
}
tr1::shared_ptr<Bob> john(new Bob, deleter );
**/

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
