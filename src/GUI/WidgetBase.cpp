#include "WidgetBase.hpp"

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

}
void WidgetBase::f_initialize(const WidgetBaseData& data)
{
    //initialize data
}


/**IO**/
IOBaseReturn WidgetBase::input(IOBaseArgs)
{
    IOBase::input(rInput, rCommand);
}


/**PRIVATE**/
void WidgetBase::f_callback(const tgui::Callback& callback)
{
    //override and callbacks here
}
void WidgetBase::f_MouseEntered()
{
    f_varEvent("", Event::MouseEntered);
}
void WidgetBase::f_LeftMouseClicked()
{
    f_varEvent("", Event::LeftMouseClicked);
}
void WidgetBase::f_MouseLeft()
{
    f_varEvent("", Event::MouseLeft);
}
