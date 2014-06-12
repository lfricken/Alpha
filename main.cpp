#include "stdafx.h"
#include "defaults.h"
#include "Game.h"

#include "CollisionCategory.h"

/**defaults must be defined first because they may be, and are, used in the creation of other things**/
/**================**/
/**====DEFAULTS====**/
/**================**/
namespace def
{


/**IOBASE**/
namespace io
{
const ClassType classType = ClassType::UNKNOWN;
const bool isEnabled = true;
const std::string name = "defaultName";
const unsigned long long int ID = -1;//max value
}
/**IOBASE**/


/**PHYSICS**/
namespace phys
{
const Shape shape = Shape::BOX;
const Category category = Category::None;
const Mask mask = Mask::None;
const bool isSensor = false;
const b2Vec2 offset = b2Vec2(0, 0);
const b2Vec2 halfSize = b2Vec2(0.25, 0.25);
const float density = 1.0;
const float friction = 0.3;
const float restitution = 0.2;
const float rotation = 0.0;//degrees CW
}
/**PHYSICS**/


/**GRAPHICS**/
namespace gfx
{
const float rotation = 0;
const std::string texName = "textures/default.png";
const sf::Color color = sf::Color::White;
const sf::Vector2f texTileSize = sf::Vector2f(128, 128);
const sf::Vector2f texTile = sf::Vector2f(0, 0);///deprecated

extern const sf::Vector2f position = sf::Vector2f(0, 0);
extern const sf::Vector2f scale = sf::Vector2f(128, 128);
}
/**GRAPHICS**/


/**CHUNK**/
namespace cnk
{
const b2BodyType bodyType = b2BodyType::b2_staticBody;
const b2Vec2 position = b2Vec2(0,0);
const bool isBullet = false;
const float maxZoom = 16.0f;
const float minZoom = 0.5f;
const bool controlEnabled = true;
}
/**CHUNK**/


/**CONTROLERS**/
namespace cntrl
{
const std::string targetName = io::name;
const PlayerMode playerMode = PlayerMode::God;
const sf::Vector2f cameraPos = sf::Vector2f(0, 0);
const sf::Vector2f cameraSize = sf::Vector2f(800, 600);
const PlayerState playerState = PlayerState::Playing;
}
/**CONTROLERS**/


/**GUI**/
namespace gui
{
const sf::Color backgroundColor = sf::Color::White;
const std::string buttonText = "FixThis";
const std::string config = "TGUI/widgets/Black.conf";
const sf::Vector2f position = sf::Vector2f(10, 10);
const sf::Vector2f size = sf::Vector2f(100, 50);
}
/**GUI**/
}

/**================**/
/**====DEFAULTS====**/
/**================**/


/**CONVERSIONS**/
extern const float pi = 3.14159;
const int scale = 128;//use this when converting from Box2D coordinates, to sfml coordinates
/**CONVERSIONS**/


/**===============**/
/**====GLOBALS====**/
/**===============**/
Game game;//globals.h
/**===============**/
/**====GLOBALS====**/
/**===============**/

int main()
{
    ///we should load the defaults from a file, in which case they shouldn't be a const
    sf::Texture tex;
    std::cout << "\nMax Texture Size: [" << tex.getMaximumSize() << "].";
    tex.loadFromFile("textures/default.png");
    std::cout << "\nTexture Size: [" << tex.getSize().x << "].";


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
