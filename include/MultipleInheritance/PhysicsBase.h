#ifndef PHYSICSBASE_H
#define PHYSICSBASE_H

#include <stdafx.h>

struct PhysicsBaseData
{
    b2Vec2 offset;/**physics**///offset of the box from the center
    b2Vec2 halfSize;//half size of the box2dBox, also controls the tileSize in graphics
    float density;
    float friction;
    float restitution;
    float rotation;//degrees
    b2Body* pBody;
};


class PhysicsBase
{
public:
    PhysicsBase();
    virtual ~PhysicsBase();

    virtual b2World& getWorld();

    virtual b2Fixture& getFixture() const;
    virtual b2Fixture& getFixture();
    virtual void setFixture(b2Fixture* fix);

    virtual b2Body& getBody() const;
    virtual b2Body& getBody();
    virtual void setBody(b2Body* fix);

    virtual const b2PolygonShape& getShape() const;
    virtual b2PolygonShape& getShape();

    virtual const b2FixtureDef& getFixtureDef() const;
    virtual b2FixtureDef& getFixtureDef();


protected:
    b2PolygonShape m_shape;
    b2FixtureDef m_fixtureDef;

    b2Body* m_pBody;//pointer
    b2Fixture* m_pFixture;//pointer


    static b2World& m_rPhysWorld;

private:
};

#endif // PHYSICSBASE_H