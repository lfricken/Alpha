#include "WidgetBase.hpp"

using namespace leon;

WidgetBase::WidgetBase(const WidgetBaseData& rData) : IOBase(rData)
{

}
void WidgetBase::f_assign(tgui::Widget* pWidget)
{
    m_pWidget = pWidget;
}
WidgetBase::~WidgetBase()
{

}
void WidgetBase::enable()
{
    m_pWidget->enable();
}
void WidgetBase::disable()
{
    m_pWidget->disable();
}
void WidgetBase::show()
{
    m_pWidget->show();
    m_pWidget->moveToFront();
}
void WidgetBase::hide()
{
    m_pWidget->hide();
}


/**IO**/
IOBaseReturn WidgetBase::input(IOBaseArgs)
{
    IOBase::input(rInput, rCommand);
}


/**PRIVATE**/
void WidgetBase::f_callback(const tgui::Callback& callback)
{
    (void)callback;//shutup the compiler about unused
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
