#include "Hull.h"

Hull::Hull() : Module()
{
    HullData data;
    f_initialize(data);
}
Hull::Hull(const HullData& data) : Module(static_cast<ModuleData>(data))
{
    f_initialize(data);
}
Hull::~Hull()
{

}
void Hull::f_initialize(const HullData& data)
{

}
