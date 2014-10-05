#ifndef PANEL_H
#define PANEL_H

#include "WidgetBase.hpp"

namespace leon
{

struct PanelData : public WidgetBaseData
{
    PanelData() :
        WidgetBaseData(),
        backgroundColor(defaults::gui::backgroundColor)
    {
    type = ClassType::PANEL;
    }
    sf::Color backgroundColor;
    std::string backgroundTex;
};

class Panel : public WidgetBase
{
public:
    Panel(tgui::Gui& gui, const PanelData& data);
    Panel(tgui::Container& container, const PanelData& data);
    ~Panel();

    /**GENERIC**/
    WidgetBase* getTarget(const std::string& targetName);
    tgui::Panel::Ptr getPanelPtr() const;
    void add(std::tr1::shared_ptr<WidgetBase> sp_widget);
    void setState(PlayerState state);
    void toggleHide();

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
protected:
    virtual void f_callback(const tgui::Callback& callback);

private:
    virtual void f_initialize(const PanelData& data);
    std::vector<std::tr1::shared_ptr<WidgetBase> > m_widgetList;

    tgui::Panel::Ptr m_pPanel;//the gui panel
    tgui::ChildWindow::Ptr m_pChildWindow;
};
}

#endif // PANEL_H
