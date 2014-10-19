#include "Panel.hpp"
#include "Sort.hpp"
#include "globals.hpp"

using namespace leon;


Panel::Panel(tgui::Gui& gui, const PanelData& rData) : WidgetBase(rData), m_pPanel(gui, rData.name)
{
    f_initialize(rData);
}
Panel::Panel(tgui::Container& container, const PanelData& rData) : WidgetBase(rData), m_pPanel(container, rData.name)
{
    f_initialize(rData);
}
Panel::~Panel()
{

}//..\..\..\Engines\JSON\lib\libjsoncpp.dll.a
void Panel::f_initialize(const PanelData& rData)
{
    if(rData.hidePanelButton)//create a button on the panel (top right) that will hide it
    {/*
        int buttonSize = 20;
        ButtonData closeButton;
        closeButton.size = sf::Vector2f(20,20);
        closeButton.buttonText = "X";
        closeButton.position = sf::Vector2f(rData.size.x-20, 400);

        leon::ButtonData htpButData;
        htpButData.size = sf::Vector2f(275,50);
        htpButData.buttonText = "How To Play";
        htpButData.position = sf::Vector2f(20, 400);
        htpButData.type = ClassType::BUTTON;
        Courier htpMessage;
        htpMessage.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
        htpMessage.package.reset("ecg", "show", voidPacket, 0, Destination::UNIVERSE, false);
        htpButData.courierList.push_back(htpMessage);*/
    }

    f_assign(m_pPanel.get());
    m_pPanel->setPosition(rData.position);
    m_pPanel->setSize(rData.size.x, rData.size.y);
    m_pPanel->setBackgroundColor(rData.backgroundColor);
    if(rData.backgroundTex != "")
        m_pPanel->setBackgroundTexture(game.getTextureAllocator().request(rData.backgroundTex));

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
    (void)state;//shutup the compiler about unused
}


/**IO**/
IOBaseReturn Panel::input(IOBaseArgs)
{
    (void)rInput;//shutup the compiler about unused
    if(rCommand == "show")
        m_pPanel->show();
    else if(rCommand == "hide")
        m_pPanel->hide();
    else if(rCommand == "toggleHide")
        toggleHide();
    else
        WidgetBase::input(rInput, rCommand);
}
void Panel::toggleHide()
{
    if(m_pPanel->isVisible())
        hide();
    else
        show();
}


/**PRIVATE**/
void Panel::f_callback(const tgui::Callback& callback)
{
    (void)callback;//shutup the compiler about unused
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
