#include "EditBox.h"

using namespace leon;

EditBox::EditBox(tgui::Gui& gui) : m_pEditBox(gui)
{
    EditBoxData data;
    f_initialize(data);
}
EditBox::EditBox(tgui::Gui& gui, const EditBoxData& data) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pEditBox(gui, data.name)
{
    f_initialize(data);
}
EditBox::EditBox(tgui::Container& container) : m_pEditBox(container)
{
    EditBoxData data;
    f_initialize(data);
}
EditBox::EditBox(tgui::Container& container, const EditBoxData& data = EditBoxData()) : WidgetBase(static_cast<WidgetBaseData>(data)), m_pEditBox(container, data.name)
{
    f_initialize(data);
}
EditBox::~EditBox()
{

}
void EditBox::f_initialize(const EditBoxData& data)
{
    m_pEditBox->load(data.configFile);
    m_pEditBox->setPosition(data.position);
    m_pEditBox->setText(data.startingText);
    m_pEditBox->setSize(data.size.x, data.size.y);

    m_pEditBox->bindCallbackEx(&EditBox::f_callback, this, tgui::EditBox::AllEditBoxCallbacks);
}


/**GENERIC**/


/**IO**/
IOBaseReturn EditBox::input(IOBaseArgs)
{
    if(rCommand == "trigger")
       trigger();
    else
        WidgetBase::input(rInput, rCommand);
}
void EditBox::trigger()
{
    f_varEvent(m_pEditBox->getText(), Event::Triggered);
}




/**PRIVATE**/
void EditBox::f_callback(const tgui::Callback& callback)
{
    if(callback.trigger == tgui::EditBox::MouseEntered)
    {
        f_MouseEntered();
    }
    else if(callback.trigger == tgui::EditBox::LeftMouseClicked)
    {
        f_LeftMouseClicked();
    }
    else if(callback.trigger == tgui::EditBox::MouseLeft)
    {
        f_MouseLeft();
    }
    else if(callback.trigger == tgui::EditBox::TextChanged)
    {
        f_TextChanged();
    }
    else if(callback.trigger == tgui::EditBox::ReturnKeyPressed)
    {
        f_ReturnKeyPressed();
    }
    else
    {

    }
}
void EditBox::f_MouseEntered()
{
    f_varEvent(m_pEditBox->getText(), Event::MouseEntered);
}
void EditBox::f_LeftMouseClicked()
{
    f_varEvent(m_pEditBox->getText(), Event::LeftMouseClicked);
}
void EditBox::f_MouseLeft()
{
    f_varEvent(m_pEditBox->getText(), Event::MouseLeft);
}
void EditBox::f_TextChanged()
{
    f_varEvent(m_pEditBox->getText(), Event::TextChanged);
}
void EditBox::f_ReturnKeyPressed()
{
    f_varEvent(m_pEditBox->getText(), Event::ReturnKeyPressed);
}
