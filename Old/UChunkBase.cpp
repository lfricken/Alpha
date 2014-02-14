#include "Universe/UChunkBase.h"


UChunkBase::UChunkBase(b2World& rPhysWorld, b2Vec2 coordinate) : m_rPhysWorld(rPhysWorld)
{
    /*///dynamic chunk code
        b2BodyDef bodyDef;//creates and sets body data
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = coordinate;
        m_pBody = m_rPhysWorld.CreateBody(&bodyDef);//Lets the world know it exists
        */
}

UChunkBase::~UChunkBase()
{
    //dtor
}



    /*dynamic chunk code
    b2PolygonShape boxShape;//creates some shape named boxShape
    boxShape.SetAsBox(0.5, 0.5, physicsBase.getOffset(), physicsBase.getRotation());

    b2FixtureDef fixtureDef;//creates and sets fixture data
    fixtureDef.shape = &boxShape;//makes the shape of the fixture the same as boxShape
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.4f;
    fixtureDef.restitution = 0.2;

    physicsBase.setFixture(m_pBody->CreateFixture(&fixtureDef));
    */

