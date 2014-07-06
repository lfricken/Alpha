#include "Button.h"

using namespace leon;

Button::Button(tgui::Gui& gui) : m_pButton(gui)
{
    ButtonData data;
    f_initialize(data);
}
Button::Button(tgui::Gui& gui, const ButtonData& data) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pButton(gui, data.name)
{
    f_initialize(data);
}
Button::Button(tgui::Container& container) : m_pButton(container)
{
    ButtonData data;
    f_initialize(data);
}
Button::Button(tgui::Container& container, const ButtonData& data = ButtonData()) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pButton(container, data.name)
{
    f_initialize(data);
}
Button::~Button()
{

}
void Button::f_initialize(const ButtonData& data)
{
    m_pButton->load(data.configFile);
    m_pButton->setPosition(data.position);
    m_pButton->setText(data.buttonText);
    m_pButton->setSize(data.size.x, data.size.y);

    m_pButton->bindCallbackEx(&Button::f_callback, this, tgui::Button::AllButtonCallbacks);
}


/**IO**/
IOBaseReturn Button::input(IOBaseArgs)
{
    WidgetBase::input(rInput, rCommand);
}




/**PRIVATE**/
void Button::f_callback(const tgui::Callback& callback)
{
    if(callback.trigger == tgui::Button::MouseEntered)
    {
        f_MouseEntered();
    }
    else if(callback.trigger == tgui::Button::LeftMouseClicked)
    {
        f_LeftMouseClicked();
    }
    else if(callback.trigger == tgui::Button::MouseLeft)
    {
        f_MouseLeft();
    }
}
void Button::f_MouseEntered()
{
    f_varEvent("", Event::MouseEntered);
}
void Button::f_LeftMouseClicked()
{
    f_varEvent("", Event::LeftMouseClicked);
}
void Button::f_MouseLeft()
{
    f_varEvent("", Event::MouseLeft);
}
