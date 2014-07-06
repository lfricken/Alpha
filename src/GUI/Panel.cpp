#include "Panel.h"
#include "Sort.h"

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
    m_pPanel->bindCallbackEx(&Panel::f_callback, this, tgui::Panel::AllPanelCallbacks);
}


/**GENERIC**/
WidgetBase* Panel::getTarget(const std::string& targetName)
{
    auto it_end = m_widgetList.cend();
    for(auto it = m_widgetList.begin(); it != it_end; ++it)
    {
        if((*it)->getName() == targetName)
            return &(**it);
    }
    return NULL;
    ///ERROR LOG
}
tgui::Panel::Ptr Panel::getPanelPtr() const
{
    return m_pPanel;
}
void Panel::add(std::tr1::shared_ptr<WidgetBase> sp_widget)
{
    InsertPtrVector(m_widgetList, &IOBase::getID, sp_widget);
}
void Panel::setState(PlayerState state)
{

}


/**IO**/
IOBaseReturn Panel::input(IOBaseArgs)
{
    WidgetBase::input(rInput, rCommand);
}


/**PRIVATE**/
void Panel::f_callback(const tgui::Callback& callback)
{
    /** EXAMPLE CODE
    if(true)
    {
        std::vector<tgui::Widget::Ptr>(m_pPanel->getWidgets());
        //std::string blab = callback.;
        //std::cout << blab;
    }
    else
    {
        std::cout << "\nCallback";
        std::cout << "(" << callback.mouse.x << "," << callback.mouse.y << ")";
    }
    **/
}
