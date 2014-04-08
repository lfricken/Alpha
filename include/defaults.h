#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "stdafx.h"
#include "CollisionCategory.h"
#include "Shape.h"
#include "ClassType.h"

/**IOBASE**/
extern const ClassType defaultClassType;
extern const bool defaultIsEnabled;
extern const std::string defaultName;
extern const unsigned int defaultID;

#define IOBaseReturn void
#define IOBaseArgs sf::Packet& rInput
/**IOBASE**/


/**PHYSICS**/
extern const Shape defaultShape;
extern const int defaultCollisionCategory;
extern const int defaultMaskBits;
extern const bool defaultIsSensor;
extern const b2Vec2 defaultOffset;
extern const b2Vec2 defaultHalfSize;
extern const float defaultDensity;
extern const float defaultFriction;
extern const float defaultRestitution;
extern const float defaultRotation;
/**PHYSICS**/


/**GRAPHICS**/
extern const std::string defaultTexName;
extern const sf::Color defaultColor;
extern const sf::Vector2f defaultTexTileSize;
extern const sf::Vector2f defaultTexTile;
/**GRAPHICS**/


/**CHUNK**/
extern const b2BodyType defaultBodyType;
extern const b2Vec2 defaultPosition;
extern const bool defaultIsBullet;
extern const float defaultMaxZoom;
extern const float defaultMinZoom;
/**CHUNK**/


/**CONTROLERS**/
extern const std::string defaultTargetName;
extern const std::string defaultPlayerMode;
extern const sf::Vector2f defaultCameraPos;
extern const sf::Vector2f defaultCameraSize;
/**CONTROLERS**/



/**GUI**/
namespace leon
{
extern const sf::Color defaultBackgroundColor;
extern const std::string defaultButtonText;
extern const std::string defaultConfig;
extern const sf::Vector2f defaultPosition;
extern const sf::Vector2f defaultSize;
}
/**GUI**/

/**CONVERSIONS**/
extern const int scale;//use this when converting from Box2D coordinates, to sfml coordinates
/**CONVERSIONS**/

#endif // DEFAULTS_H
