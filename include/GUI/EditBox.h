#ifndef EDITBOX_H
#define EDITBOX_H

#include "WidgetBase.h"

namespace leon
{
struct EditBoxData : public WidgetBaseData
{
    EditBoxData() :
        WidgetBaseData(),
        startingText(def::gui::buttonText)
    {
        type = ClassType::EDITBOX;
    }

    std::string startingText;
};


class EditBox : public WidgetBase
{
public:
    EditBox(tgui::Gui& gui);
    EditBox(tgui::Gui& gui, const EditBoxData& data);///menubar struct constructor
    EditBox(tgui::Container& container);
    EditBox(tgui::Container& container, const EditBoxData& data);
    virtual ~EditBox();

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
    virtual void trigger();
protected:
    virtual void f_callback(const tgui::Callback& callback);
    void f_MouseEntered();
    void f_MouseLeft();
    void f_LeftMouseClicked();
    void f_TextChanged();
    void f_ReturnKeyPressed();

private:
    virtual void f_initialize(const EditBoxData& data);

    tgui::EditBox::Ptr m_pEditBox;//pointer to our editbox inside gui
};
}
#endif // EDITBOX_H
