#ifndef PHYSICSBASE_H
#define PHYSICSBASE_H

#include "stdafx.hpp"
#include "IOBase.hpp"

class Chunk;

struct PhysicsBaseData : public IOBaseData//initialized
{
    PhysicsBaseData() :
        IOBaseData(),
        shape(defaults::fixture::shape),
        categoryBits(defaults::fixture::category),
        maskBits(defaults::fixture::mask),
        isSensor(defaults::fixture::isSensor),
        offset(defaults::fixture::offset),
        halfSize(defaults::fixture::halfSize),
        density(defaults::fixture::density),
        friction(defaults::fixture::friction),
        restitution(defaults::fixture::restitution),
        rotation(defaults::fixture::rotation),
        pBody(NULL),
        pChunk(NULL)
        {}

    Shape shape;
    Category categoryBits;//what type of object we are
    Mask maskBits;//what we will try and collide with
    bool isSensor;
    b2Vec2 offset;//offset of the box from the center for physics
    b2Vec2 halfSize;//half size of the box2dBox, also controls the tileSize in graphics
    float density;
    float friction;
    float restitution;
    float rotation;///degrees CW, should be CCW, check this
    b2Body* pBody;
    Chunk* pChunk;
    std::vector<b2Vec2> vertices;
};


class PhysicsBase : public IOBase
{
public:
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
