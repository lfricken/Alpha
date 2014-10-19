#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include "IOBase.hpp"

namespace leon
{
struct WidgetBaseData : public IOBaseData
{
    WidgetBaseData():
        IOBaseData(),
        startHidden(false),
        configFile(defaults::gui::config),
        position(defaults::gui::position),
        size(defaults::gui::size)
    {}
    bool startHidden;
    std::string configFile;
    sf::Vector2f position;/**upper left corner**/
    sf::Vector2f size;
};

class WidgetBase : public IOBase
{
public:
    WidgetBase(const WidgetBaseData& rData);
    virtual ~WidgetBase();

    virtual void enable() final;
    virtual void disable() final;
    virtual void show() final;
    virtual void hide() final;

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
protected:
    void f_assign(tgui::Widget* pWidget);//must assign child widget

    virtual void f_callback(const tgui::Callback& callback);
    void f_MouseEntered();
    void f_LeftMouseClicked();
    void f_MouseLeft();

private:
    bool m_startHidden;
    tgui::Widget* m_pWidget;
};
}
#endif // WIDGETBASE_H
