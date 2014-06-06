#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "stdafx.h"
#include "CollisionCategory.h"
#include "Shape.h"
#include "ClassType.h"
#include "PlayerMode.h"

namespace def
{

/**IOBASE**/
namespace io
{
extern const ClassType defaultClassType;
extern const bool defaultIsEnabled;
extern const std::string defaultName;
extern const unsigned long long int defaultID;

#define IOBaseReturn void//these defines are used to take headache out of changing them
#define IOBaseArgs sf::Packet& rInput
}
/**IOBASE**/


/**PHYSICS**/
namespace phys
{
extern const Shape defaultShape;
extern const Category defaultCategory;
extern const MaskBits defaultMaskBits;
extern const bool defaultIsSensor;
extern const b2Vec2 defaultOffset;
extern const b2Vec2 defaultHalfSize;
extern const float defaultDensity;
extern const float defaultFriction;
extern const float defaultRestitution;
extern const float defaultRotation;//degrees CW
}
/**PHYSICS**/


/**GRAPHICS**/
namespace gfx
{
extern const std::string defaultTexName;
extern const sf::Color defaultColor;
extern const sf::Vector2f defaultTexTileSize;
extern const sf::Vector2f defaultTexTile;
}
/**GRAPHICS**/


/**CHUNK**/
namespace cnk
{
extern const b2BodyType defaultBodyType;
extern const b2Vec2 defaultPosition;
extern const bool defaultIsBullet;
extern const float defaultMaxZoom;
extern const float defaultMinZoom;
extern const bool defaultCntrlEnabled;
}
/**CHUNK**/


/**CONTROLERS**/
namespace cntrl
{
extern const std::string defaultTargetName;
extern const PlayerMode defaultPlayerMode;
extern const sf::Vector2f defaultCameraPos;
extern const sf::Vector2f defaultCameraSize;
extern const PlayerState defaultPlayerState;
}
/**CONTROLERS**/


/**GUI**/
namespace gui
{
extern const sf::Color defaultBackgroundColor;
extern const std::string defaultButtonText;
extern const std::string defaultConfig;
extern const sf::Vector2f defaultPosition;
extern const sf::Vector2f defaultSize;
}
/**GUI**/

}


/**CONVERSIONS**/
extern const float pi;
extern const int scale;//use this when converting from Box2D coordinates, to sfml coordinates
/**CONVERSIONS**/

#endif // DEFAULTS_H
