#include <stdafx.h>
#include <Game/Game.h>

using namespace std;

//sf::ContextSettings settings = {4};
Game game;
int scale = 128;


class Bob
{
public:
    void destroy(Bob* p) {cout << "\nDestroyed";}
};
void deleter(Bob* p)
{
    cout << "\nWorks";
}

//std::shared_ptr<SDL_Surface>(SDL_LoadBMP(....), DeleteSurface);

int main()
{
    game.run();
    tr1::shared_ptr<Bob> john(new Bob, deleter );
    return 0;
}
