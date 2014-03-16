#include "GModule.h"
#include "globals.h"


using namespace sf;

GModule::GModule(GModuleData& data) : PhysicsBase(data.physicsData, data.baseData), GraphicsBase(data.graphicsData, data.physicsData.halfSize, data.physicsData.offset)
{
    m_pFixture->SetUserData(this);
}
GModule::~GModule()
{
}
int GModule::damage(int damage)
{
    incTexTile();
    return PhysicsBase::damage(damage);
}

