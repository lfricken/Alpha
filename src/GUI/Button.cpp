#include "Button.h"

//using namespace leon;

leon::Button::Button(tgui::Gui& gui) : m_pButton(gui)
{
    ButtonData data;
    f_initialize(data);
}
leon::Button::Button(tgui::Gui& gui, const ButtonData& data) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pButton(gui)
{
    f_initialize(data);
}
leon::Button::Button(tgui::Container& container) : m_pButton(container)
{
    ButtonData data;
    f_initialize(data);
}
leon::Button::Button(tgui::Container& container, const ButtonData& data) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pButton(container)
{
    f_initialize(data);
}
leon::Button::~Button()
{

}
void leon::Button::f_initialize(const ButtonData& data)
{
    m_pButton->load(data.configFile);
    m_pButton->setPosition(data.position);
    m_pButton->setText(data.buttonText);
    m_pButton->setSize(data.size.x, data.size.y);
    m_pButton->bindCallbackEx(&leon::Button::callback, this, tgui::Button::LeftMouseClicked);
}
void leon::Button::callback(const tgui::Callback& callback)
{
    std::cout << m_name << " was clicked. Checking for events...";
    std::cout << " none found.";
}

