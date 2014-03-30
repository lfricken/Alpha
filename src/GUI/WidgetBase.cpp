#include "WidgetBase.h"

using namespace leon;

WidgetBase::WidgetBase()
{
    WidgetBaseData data;
    f_initialize(data);
}
WidgetBase::WidgetBase(const WidgetBaseData& data) : IOBase(static_cast<IOBaseData>(data))
{
    f_initialize(data);
}
WidgetBase::~WidgetBase()
{
    //dtor
}
void WidgetBase::callback(const tgui::Callback& callback)
{
    //override and callbacks here
}
void WidgetBase::f_initialize(const WidgetBaseData& data)
{

}
