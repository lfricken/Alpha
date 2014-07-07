#ifndef PHYSICSBASE_H
#define PHYSICSBASE_H

#include "stdafx.h"
#include "IOBase.h"
#include "CollisionCategory.h"

struct PhysicsBaseData : public IOBaseData//initialized
{
    PhysicsBaseData() :
        IOBaseData(),
        shape(def::phys::shape),
        categoryBits(def::phys::category),
        maskBits(def::phys::mask),
        isSensor(def::phys::isSensor),
        offset(def::phys::offset),
        halfSize(def::phys::halfSize),
        density(def::phys::density),
        friction(def::phys::friction),
        restitution(def::phys::restitution),
        rotation(def::phys::rotation),
        pBody(NULL)
        {}

    Shape shape;
    Category categoryBits;//what type of object we are
    Mask maskBits;//what we will try and collide with
    bool isSensor;
    b2Vec2 offset;/**physics**///offset of the box from the center
    b2Vec2 halfSize;//half size of the box2dBox, also controls the tileSize in graphics
    float density;
    float friction;
    float restitution;
    float rotation;//degrees CW
    b2Body* pBody;
    std::vector<b2Vec2> vertices;
};


class PhysicsBase : public IOBase
{
public:///MAYBE we shouldn't have this many functions???
    PhysicsBase();
    PhysicsBase(const PhysicsBaseData& data);
    virtual ~PhysicsBase();

    virtual int startContact(PhysicsBase* other);
    virtual int endContact(PhysicsBase* other);
    virtual int preSolveContact(PhysicsBase* other);
    virtual int postSolveContact(PhysicsBase* other);

    virtual bool physUpdate();//used to implement special physical forces and stuff

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
    float getAproximateMass() const;

protected:
    std::tr1::shared_ptr<b2Shape> m_shape;
    b2FixtureDef m_fixtureDef;

    b2Body* m_pBody;//pointer, no ownership
    b2Fixture* m_pFixture;//pointer, no ownership

    b2World& m_rPhysWorld;

private:
    virtual void f_initialize(const PhysicsBaseData& data);
};

#endif // PHYSICSBASE_H
