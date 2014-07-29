#ifndef PHYSICSBASE_H
#define PHYSICSBASE_H

#include "stdafx.h"
#include "IOBase.h"
#include "CollisionCategory.h"

class Chunk;

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
        pBody(NULL),
        pChunk(NULL)
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
    Chunk* pChunk;
    std::vector<b2Vec2> vertices;
};


class PhysicsBase : public IOBase
{
public:///MAYBE we shouldn't have this many functions???
    PhysicsBase();
    PhysicsBase(const PhysicsBaseData& data);
    virtual ~PhysicsBase();


    /**PHYSICS**/
    virtual int startContact(PhysicsBase* other);
    virtual int endContact(PhysicsBase* other);
    virtual int preSolveContact(PhysicsBase* other);
    virtual int postSolveContact(PhysicsBase* other);

    virtual bool physUpdate();//used to implement special physical forces and stuff
    b2Fixture* getFixture();
    Chunk* getChunk();


    /**CONST**/
    const b2Body* getBody() const;
    const b2Fixture* getFixture() const;
    float getMass() const;
    b2Vec2 getCenter() const;

protected:
    std::tr1::shared_ptr<b2Shape> m_spShape;
    b2FixtureDef m_fixtureDef;

    Chunk* m_pChunk;
    b2Body* m_pBody;//pointer, no ownership
    b2Fixture* m_pFixture;//pointer, no ownership

    float m_mass;//computed in our constructor
    b2Vec2 m_halfSize;
private:
    virtual void f_initialize(const PhysicsBaseData& data);
};

#endif // PHYSICSBASE_H
