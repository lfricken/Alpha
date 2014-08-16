#include "BaseGraphicsComponent.hpp"
#include "GraphicsComponentFactory.hpp"
#include "globals.hpp"

BaseGraphicsComponent::BaseGraphicsComponent(const BaseGraphicsComponentData& rData)
{
    m_velVec = b2Vec2(0,0);
    m_isVisible = !rData.startHidden;//reverse it
    m_gfxLayer = rData.gfxLayer;
    m_texName = rData.texName;
    m_pFactoryParent = rData.pParent;
}
BaseGraphicsComponent::~BaseGraphicsComponent()
{

}
const std::string& BaseGraphicsComponent::getTexName() const
{
    return m_texName;
}
GraphicsLayer BaseGraphicsComponent::getGfxLayer() const
{
    return m_gfxLayer;
}
void BaseGraphicsComponent::free()
{
    m_pFactoryParent->freeComponent(this);
}
void BaseGraphicsComponent::setVisibility(bool visible)
{
    m_isVisible = visible;
}
bool BaseGraphicsComponent::isVisible() const
{
    return m_isVisible;
}
void BaseGraphicsComponent::draw(sf::RenderTexture& image, sf::RenderTexture& vecField, const b2Vec2& rCameraVel)
{

    if(isVisible())
    {
        b2Vec2 relative = m_velVec-rCameraVel;

        game.m_shader.setParameter("texture", sf::Shader::CurrentTexture);
        game.m_shader.setParameter("velocity", relative.x, relative.y);
        game.m_shader.setParameter("angle", getRotation());

        game.rendText_1.draw(getDrawable(), &game.m_shader);
    }
}
void BaseGraphicsComponent::setVelocity(const b2Vec2& rVel)
{
    m_velVec = rVel;
}
