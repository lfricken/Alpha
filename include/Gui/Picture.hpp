#ifndef PICTURE_HPP
#define PICTURE_HPP

#include "WidgetBase.hpp"

namespace leon
{

struct PictureData : public WidgetBaseData
{
    PictureData() :
        WidgetBaseData(),
        texName("textures/default.png")
    {
        type = ClassType::DECORATION;
    }
    std::string texName;
};

class Picture : public WidgetBase
{
public:
    Picture(tgui::Gui& rGui, const PictureData& rData);
    Picture(tgui::Container& rContainer, const PictureData& rData);
    virtual ~Picture();

protected:
private:
    void f_initialize(const PictureData& data);

    virtual void f_callback(const tgui::Callback& callback);
    virtual void f_MouseEntered();
    virtual void f_MouseLeft();
    virtual void f_LeftMouseClicked();

    tgui::Picture::Ptr m_pPicture;//pointer to our button in the gui
};
}
#endif // PICTURE_HPP
