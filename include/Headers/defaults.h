#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "stdafx.h"
#include "CollisionCategory.h"
#include "Shape.h"
#include "ClassType.h"
#include "PlayerMode.h"
#include "AnimationState.h"
#include "GraphicsLayer.h"

namespace def
{

/**IOBASE**/
namespace io
{
extern const ClassType classType;
extern const bool isEnabled;
extern const std::string name;
extern const unsigned long long int ID;

#define IOBaseReturn void//these defines are used to take headache out of changing them
#define IOBaseArgs sf::Packet& rInput, const std::string& rCommand
}
/**IOBASE**/


/**PHYSICS**/
namespace phys
{
extern const Shape shape;
extern const Category category;
extern const Mask mask;
extern const bool isSensor;
extern const b2Vec2 offset;
extern const b2Vec2 halfSize;
extern const float density;
extern const float friction;
extern const float restitution;
extern const float rotation;//degrees CW
}
/**PHYSICS**/


/**GRAPHICS**/
namespace gfx
{
extern const float rotation;//
extern const std::string texName;
extern const sf::Color color;
extern const sf::Vector2f texTileSize;
extern const sf::Vector2f texTile;

extern const sf::Vector2f position;
extern const sf::Vector2f scale;
extern const AnimationState animState;
extern GraphicsLayer layer;
}
/**GRAPHICS**/


/**CHUNK**/
namespace cnk
{
extern const b2BodyType bodyType;
extern const b2Vec2 position;
extern const bool isBullet;
extern const float maxZoom;
extern const float minZoom;
extern const bool controlEnabled;
}
/**CHUNK**/


/**CONTROLERS**/
namespace cntrl
{
extern const std::string targetName;
extern const PlayerMode playerMode;
extern const sf::Vector2f cameraPos;
extern const PlayerState playerState;
}
/**CONTROLERS**/


/**GUI**/
namespace gui
{
extern const sf::Color backgroundColor;
extern const std::string buttonText;
extern const std::string config;
extern const sf::Vector2f position;
extern const sf::Vector2f size;
}
/**GUI**/

}


/**CONVERSIONS**/
extern const float pi;
extern const int scale;//use this when converting from Box2D coordinates, to sfml coordinates
/**CONVERSIONS**/

#endif // DEFAULTS_H
