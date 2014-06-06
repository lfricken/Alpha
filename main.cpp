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
const ClassType defaultClassType = ClassType::UNKNOWN;
const bool defaultIsEnabled = true;
const std::string defaultName = "defaultName";
const unsigned long long int defaultID = -1;//max value
}
/**IOBASE**/


/**PHYSICS**/
namespace phys
{
const Shape defaultShape = Shape::BOX;
const Category defaultCategory = Category::Projectile;
const MaskBits defaultMaskBits = MaskBits::All;
const bool defaultIsSensor = false;
const b2Vec2 defaultOffset = b2Vec2(0, 0);
const b2Vec2 defaultHalfSize = b2Vec2(0.25, 0.25);
const float defaultDensity = 1.0;
const float defaultFriction = 0.3;
const float defaultRestitution = 0.3;
const float defaultRotation = 0.0;//degrees CW
}
/**PHYSICS**/


/**GRAPHICS**/
namespace gfx
{
const std::string defaultTexName = "textures/dev_128x128.png";
const sf::Color defaultColor = sf::Color::White;
const sf::Vector2f defaultTexTileSize = sf::Vector2f(128, 128);
const sf::Vector2f defaultTexTile = sf::Vector2f(0, 0);
}
/**GRAPHICS**/


/**CHUNK**/
namespace cnk
{
const b2BodyType defaultBodyType = b2BodyType::b2_dynamicBody;
const b2Vec2 defaultPosition = b2Vec2(0,0);
const bool defaultIsBullet = false;
const float defaultMaxZoom = 16.0f;
const float defaultMinZoom = 0.5f;
const bool defaultCntrlEnabled = true;
}
/**CHUNK**/


/**CONTROLERS**/
namespace cntrl
{
const std::string defaultTargetName = io::defaultName;
const PlayerMode defaultPlayerMode = PlayerMode::God;
const sf::Vector2f defaultCameraPos = sf::Vector2f(0, 0);
const sf::Vector2f defaultCameraSize = sf::Vector2f(800, 600);
const PlayerState defaultPlayerState = PlayerState::Playing;
}
/**CONTROLERS**/


/**GUI**/
namespace gui
{
const sf::Color defaultBackgroundColor = sf::Color::White;
const std::string defaultButtonText = "FixThis";
const std::string defaultConfig = "TGUI/widgets/Black.conf";
const sf::Vector2f defaultPosition = sf::Vector2f(10, 10);
const sf::Vector2f defaultSize = sf::Vector2f(100, 50);
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
