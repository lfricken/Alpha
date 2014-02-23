#include <stdafx.h>
#include <Game/Game.h>

using namespace std;

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
    game.run();

    return 0;
}
