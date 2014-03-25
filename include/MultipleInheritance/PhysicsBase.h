#ifndef PHYSICSBASE_H
#define PHYSICSBASE_H

#include "stdafx.h"
#include "IOBase.h"
#include "CollisionCategory.h"

struct PhysicsBaseData
{
    enum Shape
    {
        Box = 0,
        Octagon = 1,
        Triangle = 2,
        Circle = 3,
    };
    Shape shape;
    int categoryBits;//what type of object we are
    int maskBits;//what we will try and collide with
    bool isSensor;
    b2Vec2 offset;/**physics**///offset of the box from the center
    b2Vec2 halfSize;//half size of the box2dBox, also controls the tileSize in graphics
    float density;
    float friction;
    float restitution;
    float rotation;//degrees
    b2Body* pBody;
};


class PhysicsBase : public IOBase
{
public:///MAYBE we shouldn't have this many functions!!!
    PhysicsBase(PhysicsBaseData& data, IOBaseData& baseData);
    virtual ~PhysicsBase();

    virtual bool contact(void* other);
    virtual bool endContact(void* other);
    virtual bool physUpdate();

    virtual b2World& getWorld();

    virtual b2Fixture& getFixture() const;
    virtual b2Fixture& getFixture();
    virtual void setFixture(b2Fixture* fix);

    virtual b2Body& getBody() const;
    virtual b2Body& getBody();
    virtual void setBody(b2Body* fix);

    virtual const b2Shape& getShape() const;
    virtual b2Shape& getShape();

    virtual const b2FixtureDef& getFixtureDef() const;
    virtual b2FixtureDef& getFixtureDef();

    /**OVERRIDE**/
    virtual int damage(int damage);
    virtual int getHealth() const;

protected:
    HealthData m_health;

    b2Shape* m_shape; ///HOLY BALLS MAN, NAKED??? BE CAREFUL, WE WERE HAVING TROUBLE CASTING THIS
    b2FixtureDef m_fixtureDef;

    b2Body* m_pBody;//pointer
    b2Fixture* m_pFixture;//pointer


    b2World& m_rPhysWorld;

private:
};

#endif // PHYSICSBASE_H
