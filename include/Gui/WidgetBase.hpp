#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include "IOBase.hpp"

namespace leon
{
struct WidgetBaseData : public IOBaseData
{
    WidgetBaseData():
        IOBaseData(),
        configFile(defaults::gui::config),
        position(defaults::gui::position),
        size(defaults::gui::size)
    {}
    std::string configFile;
    sf::Vector2f position;/**upper left corner**/
    sf::Vector2f size;
};

class WidgetBase : public IOBase
{
public:
    WidgetBase();
    WidgetBase(const WidgetBaseData& data);
    virtual ~WidgetBase();

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
protected:
    virtual void f_callback(const tgui::Callback& callback);
    void f_MouseEntered();
    void f_LeftMouseClicked();
    void f_MouseLeft();

private:
    virtual void f_initialize(const WidgetBaseData& data);
};
}
#endif // WIDGETBASE_H
