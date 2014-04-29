#include "GModule.h"
#include "globals.h"


using namespace sf;


GModule::GModule():
    PhysicsBase(),
    GraphicsBase()
{

}
GModule::GModule(const GModuleData& data) :
    PhysicsBase(static_cast<PhysicsBaseData>(data)),
    GraphicsBase(static_cast<GraphicsBaseData>(data), data.halfSize, data.offset, data.rotation)
{

}
GModule::~GModule()
{

}
void GModule::f_initialize(const GModuleData& data)
{

}


int GModule::damage(int damage)
{
    incTexTile();
    return PhysicsBase::damage(damage);
}

