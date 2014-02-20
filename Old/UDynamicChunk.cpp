#include "Universe/UDynamicChunk.h"

UDynamicChunk::UDynamicChunk(b2World& rPhysWorld, b2Vec2 coordinate) : m_rPhysWorld(rPhysWorld)
{
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = coordinate;
        m_pBody = m_rPhysWorld.CreateBody(&bodyDef);
}

UDynamicChunk::~UDynamicChunk()
{

}
void UDynamicChunk::add(GModule& tempCopy)
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox(tempCopy.getHalfWidth(), tempCopy.getHalfHeight(), tempCopy.getOffset(), tempCopy.getRotation());

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = tempCopy.getDensity();
    fixtureDef.friction = tempCopy.getFriction();
    fixtureDef.restitution = tempCopy.getRestitution();

    m_GModuleList.push_back(tempCopy);

    m_GModuleList.back().setFixture(m_pBody->CreateFixture(&fixtureDef));
}
void UDynamicChunk::add(Module& tempCopy)
{
}
void UDynamicChunk::draw()
{
}
