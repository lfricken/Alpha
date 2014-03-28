#ifndef PHYSICSBASE_H
#define PHYSICSBASE_H

#include "stdafx.h"
#include "IOBase.h"
#include "CollisionCategory.h"

struct PhysicsBaseData : public IOBaseData//initialized
{
    PhysicsBaseData() :
        IOBaseData(),
        shape(defaultShape),
        categoryBits(defaultCollisionCategory),
        maskBits(defaultMaskBits),
        isSensor(defaultIsSensor),
        offset(defaultOffset),
        halfSize(defaultHalfSize),
        density(defaultDensity),
        friction(defaultFriction),
        restitution(defaultRestitution),
        rotation(defaultRotation),
        pBody(NULL)
        {}


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
    PhysicsBase();
    PhysicsBase(const PhysicsBaseData& data);
    virtual ~PhysicsBase();

    virtual int startContact(void* other);
    virtual int endContact(void* other);
    virtual int preSolveContact(void* other);
    virtual int postSolveContact(void* other);

    virtual bool physUpdate();///OBSOLETE???

    virtual b2World& getWorld();

    virtual b2Fixture* getFixture();
    virtual void setFixture(b2Fixture* fix);

    virtual b2Body* getBody();
    virtual void setBody(b2Body* fix);

    virtual b2Shape& getShape();

    virtual const b2FixtureDef& getFixtureDef() const;
    virtual b2FixtureDef& getFixtureDef();

    /**CONST OVERLOADS**/
    virtual b2Fixture* getFixture() const;
    virtual b2Body* getBody() const;
    virtual const b2Shape& getShape() const;

    /**OVERRIDE**/
    virtual int damage(int damage);
    virtual int getHealth() const;

protected:
    HealthData m_health;

    b2Shape* m_shape; ///HOLY BALLS MAN, NAKED??? BE CAREFUL, ITS BECAUSE WE WERE HAVING TROUBLE CASTING THIS
    b2FixtureDef m_fixtureDef;

    b2Body* m_pBody;//pointer
    b2Fixture* m_pFixture;//pointer


    b2World& m_rPhysWorld;

private:
    virtual void f_initialize(const PhysicsBaseData& data);
};

#endif // PHYSICSBASE_H
