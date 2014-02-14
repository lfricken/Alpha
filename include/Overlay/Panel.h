#ifndef PANEL_H
#define PANEL_H

#include <stdafx.h>
#include <MultipleInheritance/IOBase.h>

#include <Overlay/Button.h>

class Panel : public ButtonBase
{
public:
    Panel();
    ~Panel();

    void add(Button& button);//add this button to our panel

protected:
private:
    std::vector<Button> m_buttonList;
};

#endif // PANEL_H
