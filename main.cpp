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
 const std::string defaultTexName = "defaultTexture.png";
 const sf::Color defaultColor = sf::Color::White;
 const sf::Vector2f defaultTexTileSize = sf::Vector2f(64, 64);
 const sf::Vector2f defaultTexTile = sf::Vector2f(0, 0);
/**GRAPHICS**/


/**CHUNK**/
 const b2BodyType defaultBodyType = b2BodyType::b2_dynamicBody;
 const b2Vec2 defaultPosition = b2Vec2(0,0);
 const bool defaultIsBullet = false;
/**CHUNK**/



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
