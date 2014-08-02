#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "stdafx.hpp"
#include "CollisionCategory.hpp"
#include "Shape.hpp"
#include "ClassType.hpp"
#include "PlayerState.hpp"
#include "PlayerMode.hpp"
#include "AnimationState.hpp"
#include "GraphicsLayer.hpp"

namespace defaults
{

/**IOBASE**/
namespace io
{
extern ClassType classType;
extern bool isEnabled;
extern std::string name;

#define IOBaseReturn void//these defines are used to take headache out of changing them
#define IOBaseArgs sf::Packet& rInput, const std::string& rCommand
}
/**IOBASE**/


/**PHYSICS**/
namespace fixture
{
extern Shape shape;
extern Category category;
extern Mask mask;
extern bool isSensor;
extern b2Vec2 offset;
extern b2Vec2 halfSize;
extern float density;
extern float friction;
extern float restitution;
extern float rotation;///degrees CCW <----double check this
}
/**PHYSICS**/


/**GRAPHICS**/
namespace graphics
{
extern float rotation;//degrees CCW
extern std::string texName;
extern sf::Color color;
extern sf::Vector2f texTileSize;
extern sf::Vector2f texTile;

extern std::string animFile;

extern sf::Vector2f position;
extern sf::Vector2f scale;
extern AnimationState animState;
extern GraphicsLayer layer;
}
/**GRAPHICS**/


/**CHUNK**/
namespace chunk
{
extern b2BodyType bodyType;
extern b2Vec2 position;
extern bool isBullet;
extern bool controlEnabled;

extern float startMaxEnergy;
extern float maxMaxZoom;
extern float startMaxZoom;
extern float minZoom;
extern bool startAwake;
}
/**CHUNK**/


/**CONTROLERS**/
namespace control
{
extern std::string targetName;
extern PlayerMode playerMode;
extern sf::Vector2f cameraPos;
extern PlayerState playerState;
}
/**CONTROLERS**/


/**GUI**/
namespace gui
{
extern sf::Color backgroundColor;
extern std::string buttonText;
extern  std::string config;
extern sf::Vector2f position;
extern sf::Vector2f size;
}
/**GUI**/

}


/**CONVERSIONS**/
extern const float pi;
extern const int scale;//use this when converting from Box2D coordinates, to sfml coordinates
/**CONVERSIONS**/

#endif // DEFAULTS_H
