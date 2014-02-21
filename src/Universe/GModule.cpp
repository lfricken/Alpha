#include "Universe/GModule.h"
#include <globals.h>

using namespace sf;

GModule::GModule(GModuleData& data) : GraphicsBase(data.graphicsData, data.physicsData.halfSize, data.physicsData.offset)
{
    ///WE MAY WANT TO PUT THIS INSIDE OF THE PHYSICS BASE CLASS

    m_shape.SetAsBox(data.physicsData.halfSize.x, data.physicsData.halfSize.y, data.physicsData.offset, data.physicsData.rotation);//set our shape

    m_fixtureDef.shape = &m_shape;//give our shape to our fixture definition
    m_fixtureDef.density = data.physicsData.density;
    m_fixtureDef.friction = data.physicsData.friction;
    m_fixtureDef.restitution = data.physicsData.restitution;//setting our fixture data
    m_pBody = data.physicsData.pBody;

    m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);
    m_pFixture->SetUserData(static_cast<IOBase*>(this));

    type = data.type;
}
/*
GModule::GModule(const GModule& old) : GraphicsBase(data.graphicsData, data.physicsData.halfSize, data.physicsData.offset)      ///this should never be called?
{
    std::cout << "\nDGM Copy Ctor Called.";
    m_shape = old.getShape();

    m_fixtureDef = old.getFixtureDef();

    m_fixtureDef.shape = &m_shape;
    m_pBody = &old.getBody();
    m_pFixture = &old.getFixture();
}
*/
GModule::~GModule()
{
  //  std::cout << "\nDGM Dtor Called.";
}
