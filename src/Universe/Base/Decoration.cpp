#include "Decoration.h"

Decoration::Decoration() : m_gfxComp()
{
    DecorationData data;
    f_init(data);
}
Decoration::Decoration(const DecorationData& rData) : m_gfxComp(rData.gfxCompData)
{
    f_init(rData);
}
Decoration::~Decoration()
{

}
void Decoration::f_init(const DecorationData& rData)
{

}
const GraphicsComponent& Decoration::getGfxComp() const
{
    return m_gfxComp;
}
void Decoration::setPosition(const sf::Vector2f& pos)
{
    m_gfxComp.setPosition(pos);
}
void Decoration::setRotation(float r)
{
    m_gfxComp.setRotation(r);
}
void Decoration::setAnimState(AnimationState state)
{
    m_gfxComp.setAnimState(state);
}
void Decoration::update()//update animation
{
    m_gfxComp.update();
}
