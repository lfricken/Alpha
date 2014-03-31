#ifndef BUTTON_H
#define BUTTON_H

#include "WidgetBase.h"

namespace leon
{
struct ButtonData : public WidgetBaseData
{
    ButtonData() :
        WidgetBaseData(),
        buttonText(leon::defaultButtonText)
    {}

    std::string buttonText;
};


class Button : public WidgetBase
{
public:
    Button(tgui::Gui& gui);
    Button(tgui::Gui& gui, const ButtonData& data);///menubar struct constructor
    Button(tgui::Container& container);
    Button(tgui::Container& container, const ButtonData& data);
    virtual ~Button();

    virtual void callback(const tgui::Callback& callback);

protected:
/*
    virtual void f_MouseEntered();
    virtual void f_LeftMouseClicked();
    virtual void f_MouseLeft();*/
private:
    virtual void f_initialize(const ButtonData& data);
    tgui::Button::Ptr m_pButton;
};
}
#endif // BUTTON_H
