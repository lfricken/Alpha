#include "ForceFieldCore.h"

ForceFieldCore::ForceFieldCore() : GModule()
{
    ForceFieldCoreData data;
    f_initialize(data);
}
ForceFieldCore::ForceFieldCore(const ForceFieldCoreData& data) : GModule(static_cast<GModuleData>(data))
{
    f_initialize(data);
}
ForceFieldCore::~ForceFieldCore()
{

}
void ForceFieldCore::f_initialize(const ForceFieldCoreData& data)
{
    m_pForceField = data.pForceField;
}
void ForceFieldCore::destruct()
{
    GModule::destruct();

    m_pForceField->disable();
}
