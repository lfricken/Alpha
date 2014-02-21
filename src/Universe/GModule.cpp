#include "Universe/GModule.h"
#include <globals.h>

using namespace sf;

GModule::GModule(GModuleData& data) : PhysicsBase(data.physicsData), GraphicsBase(data.graphicsData, data.physicsData.halfSize, data.physicsData.offset)
{
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
