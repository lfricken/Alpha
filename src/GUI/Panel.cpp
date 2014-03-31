#include "Panel.h"

using namespace leon;

Panel::Panel(tgui::Gui& gui) : m_pPanel(gui)
{
    PanelData data;
    f_initialize(data);
}
Panel::Panel(tgui::Gui& gui, const PanelData& data) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pPanel(gui, data.name)
{
    f_initialize(data);
}
Panel::Panel(tgui::Container& container) : m_pPanel(container)
{
    PanelData data;
    f_initialize(data);
}
Panel::Panel(tgui::Container& container, const PanelData& data) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pPanel(container, data.name)
{
    f_initialize(data);
}
Panel::~Panel()
{

}
void Panel::f_initialize(const PanelData& data)
{
    m_pPanel->setPosition(data.position);
    m_pPanel->setSize(data.size.x, data.size.y);
    m_pPanel->setBackgroundColor(data.backgroundColor);
    m_pPanel->bindCallbackEx(&Panel::callback, this, tgui::Panel::AllPanelCallbacks);
}
void Panel::add(std::tr1::shared_ptr<WidgetBase> sp_widget)
{
    m_widgetList.push_back(sp_widget);
}
void Panel::callback(const tgui::Callback& callback)
{

}
