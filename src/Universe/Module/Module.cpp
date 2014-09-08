#include "Module.hpp"

Module::Module() : PhysicsBase()
{
    ModuleData data;
    f_initialize(data);
}
Module::Module(const ModuleData& data) : PhysicsBase(static_cast<PhysicsBaseData>(data))
{
    f_initialize(data);
}
Module::~Module()
{

}
void Module::f_initialize(const ModuleData& data)
{
    (void)data;
}
