#include "Armor.h"

Armor::Armor() : GModule()
{
    ArmorData data;
    f_initialize(data);
}
Armor::Armor(const ArmorData& rData) : GModule(static_cast<GModuleData>(rData))
{
    f_initialize(rData);
}
Armor::~Armor()
{

}
void Armor::f_initialize(const ArmorData& rData)
{

}
