#include "Universe/Module.h"

Module::Module(ModuleData& data) : PhysicsBase(data.physicsData)
{
    m_pFixture->SetUserData(static_cast<IOBase*>(this));

    type = data.type;
}
Module::~Module(){}
