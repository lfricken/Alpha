#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include "IOBase.h"


namespace leon
{
struct WidgetBaseData : public IOBaseData
{
    WidgetBaseData():
        IOBaseData(),
        configFile(leon::defaultConfig),
        position(leon::defaultPosition),
        size(leon::defaultSize)
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

    virtual void callback(const tgui::Callback& callback);

protected:
    void f_MouseEntered();
    void f_LeftMouseClicked();
    void f_MouseLeft();

private:
    virtual void f_initialize(const WidgetBaseData& data);
};
}
#endif // WIDGETBASE_H
