#include "GModule.h"
#include "globals.h"

using namespace sf;

GModule::GModule(GModuleData& data) : PhysicsBase(data.physicsData), GraphicsBase(data.graphicsData, data.physicsData.halfSize, data.physicsData.offset)
{
    m_pFixture->SetUserData(this);

    m_targetName = data.targetName;
    m_type = data.type;
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
}
bool GModule::input(Package& rPackage)
{
    if(rPackage.commandType == CORE)
        return coreInput(rPackage);
    else if(rPackage.commandType == PHYSICS)
        return physicsInput(rPackage);
    else if(rPackage.commandType == GRAPHICS)
        return graphicsInput(rPackage);
    else if(rPackage.commandType == SPECIAL)
        return specialInput(rPackage);
    else
        return false;
}
