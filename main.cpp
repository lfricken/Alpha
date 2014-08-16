#include "stdafx.hpp"
#include "defaults.hpp"
#include "Game.hpp"

#include "CollisionCategory.hpp"

/**defaults must be defined first because they may be, and are, used in the creation of other things**/
/**================**/
/**====DEFAULTS====**/
/**================**/
namespace defaults
{


/**IOBASE**/
namespace io
{
ClassType classType = ClassType::UNKNOWN;
bool isEnabled = true;
std::string name = "defaultName";
}
/**IOBASE**/


/**PHYSICS**/
namespace fixture
{
Shape shape = Shape::BOX;
Category category = Category::None;
Mask mask = Mask::None;
bool isSensor = false;
b2Vec2 offset = b2Vec2(0, 0);
b2Vec2 halfSize = b2Vec2(0.25, 0.25);
float density = 1.0;
float friction = 0.3;
float restitution = 0.2;
float rotation = 0.0f;///degrees CCW?
}
/**PHYSICS**/


/**GRAPHICS**/
namespace graphics
{
float rotation = 0;
std::string texName = "textures/default.png";
sf::Color color = sf::Color::White;
sf::Vector2f texTileSize = sf::Vector2f(128, 128);
sf::Vector2f texTile = sf::Vector2f(0, 0);///deprecated

std::string animFile = "textures/default.acfg";

sf::Vector2f position = sf::Vector2f(0, 0);
sf::Vector2f scale = sf::Vector2f(1, 1);
AnimationState animState ="Default";
GraphicsLayer layer = GraphicsLayer::GModules;
}
/**GRAPHICS**/


/**CHUNK**/
namespace chunk
{
b2BodyType bodyType = b2BodyType::b2_staticBody;
b2Vec2 position = b2Vec2(0,0);
bool isBullet = false;
bool controlEnabled = true;

float startMaxEnergy = 0;
float maxMaxZoom = 8;
float startMaxZoom = 5;
float minZoom = 0;
bool startAwake = true;
}
/**CHUNK**/


/**CONTROLERS**/
namespace control
{
std::string targetName = io::name;
PlayerMode playerMode = PlayerMode::God;
sf::Vector2f cameraPos = sf::Vector2f(0, 0);
PlayerState playerState = PlayerState::Playing;
}
/**CONTROLERS**/


/**GUI**/
namespace gui
{
sf::Color backgroundColor = sf::Color::White;
std::string buttonText = "FixThis";
std::string config = "TGUI/widgets/Black.conf";
sf::Vector2f position = sf::Vector2f(10, 10);
sf::Vector2f size = sf::Vector2f(100, 50);
}
/**GUI**/
}

/**================**/
/**====DEFAULTS====**/
/**================**/


/**CONVERSIONS**/
const float pi = 3.14159;
const int scale = 256;//use this when converting from Box2D coordinates, to sfml coordinates
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
//    sf::Texture tex;
 //   std::cout << "\nMax Texture Size: [" << tex.getMaximumSize() << "].";
  //  tex.loadFromFile("textures/default.png");
  //  std::cout << "\nTexture Size: [" << tex.getSize().x << "].";




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
