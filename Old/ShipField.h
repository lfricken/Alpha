#ifndef SHIPFIELD_H
#define SHIPFIELD_H

#include "Types.h"
#include "UniversalQueryCallback.h"

class Ship;

class ShipField
{
public:
    ShipField(Ship* parent);
    virtual ~ShipField();

    virtual void repulse();
    virtual void disconnect();
    virtual void setup();
protected:
private:
    Ship* m_pParent;//parent
    b2Body* m_pParentBody;

    b2Vec2 m_ourCoords;//for convienence
    b2Vec2 m_theirCoords;
    b2Vec2 m_usToThem;
    float m_distance;

    b2AABB m_fieldBounds;//field data
    float m_strength;//strength of field
    float m_radius;//radius of field

    b2World& m_rWorld;//worldly
    UniversalQueryCallback m_worldQuery;
};

#endif // SHIPFIELD_H
