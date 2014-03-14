#include "Module.h"

Module::Module(ModuleData& data) : PhysicsBase(data.physicsData, data.baseData)
{
    m_pFixture->SetUserData(static_cast<IOBase*>(this));
}
Module::~Module(){}
