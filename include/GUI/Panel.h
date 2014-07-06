#ifndef PANEL_H
#define PANEL_H

#include <WidgetBase.h>

namespace leon
{

struct PanelData : public WidgetBaseData
{
    PanelData() :
        WidgetBaseData(),
        backgroundColor(def::gui::backgroundColor)
    {
    type = ClassType::PANEL;
    }
    sf::Color backgroundColor;
};

class Panel : public WidgetBase
{
public:
    Panel(tgui::Gui& gui);
    Panel(tgui::Gui& gui, const PanelData& data);///menubar struct constructor
    Panel(tgui::Container& container);
    Panel(tgui::Container& container, const PanelData& data);
    ~Panel();

    /**GENERIC**/
    WidgetBase* getTarget(const std::string& targetName);
    tgui::Panel::Ptr getPanelPtr() const;
    void add(std::tr1::shared_ptr<WidgetBase> sp_widget);
    void setState(PlayerState state);

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
protected:
    virtual void f_callback(const tgui::Callback& callback);

private:
    virtual void f_initialize(const PanelData& data);
    std::vector<std::tr1::shared_ptr<WidgetBase> > m_widgetList;

    tgui::Panel::Ptr m_pPanel;
    tgui::ChildWindow::Ptr m_pChildWindow;
};
}

#endif // PANEL_H
