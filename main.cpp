#include "stdafx.h"
#include "defaults.h"
#include "Game.h"

/**defaults must be defined first because they may be, and are, used in the creation of other things**/
/**================**/
/**====DEFAULTS====**/
/**================**/


/**IOBASE**/
const ClassType defaultClassType = ClassType::UNKNOWN;
const bool defaultIsEnabled = true;
const std::string defaultName = "defaultName";
const unsigned int defaultID = 4294967295;//max value
/**IOBASE**/


/**PHYSICS**/
const Shape defaultShape = Shape::Box;
const int defaultCollisionCategory = CollisionCategory::Projectile;
const int defaultMaskBits = CollisionCategory::All;
const bool defaultIsSensor = true;
const b2Vec2 defaultOffset = b2Vec2(0, 0);
const b2Vec2 defaultHalfSize = b2Vec2(0.25, 0.25);
const float defaultDensity = 1.0;
const float defaultFriction = 0.3;
const float defaultRestitution = 0.3;
const float defaultRotation = 0.0;
/**PHYSICS**/


/**GRAPHICS**/
const std::string defaultTexName = "textures/dev_128x128.png";
const sf::Color defaultColor = sf::Color::White;
const sf::Vector2f defaultTexTileSize = sf::Vector2f(128, 128);
const sf::Vector2f defaultTexTile = sf::Vector2f(0, 0);
/**GRAPHICS**/


/**CHUNK**/
const b2BodyType defaultBodyType = b2BodyType::b2_dynamicBody;
const b2Vec2 defaultPosition = b2Vec2(0,0);
const bool defaultIsBullet = false;
const float defaultMaxZoom = 16.0f;
const float defaultMinZoom = 0.5f;
/**CHUNK**/


/**CONTROLERS**/
const std::string defaultTargetName = defaultName;
const std::string defaultPlayerMode = "normal";
/**CONTROLERS**/


/**GUI**/
namespace leon
{
const std::string defaultButtonText = "FixThis";
const std::string defaultConfig = "TGUI/widgets/Black.conf";
const sf::Vector2f defaultPosition = sf::Vector2f(10, 10);
const sf::Vector2f defaultSize = sf::Vector2f(100, 50);
}
/**GUI**/


/**CONVERSIONS**/
const int scale = 128;//use this when converting from Box2D coordinates, to sfml coordinates
/**CONVERSIONS**/


/**================**/
/**====DEFAULTS====**/
/**================**/




/**===============**/
/**====GLOBALS====**/
/**===============**/
Game game;//globals.h
/**===============**/
/**====GLOBALS====**/
/**===============**/



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
    //char j;
    // std::cin >> j;
    return 0;
}
