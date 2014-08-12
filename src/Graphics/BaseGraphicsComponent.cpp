#include "BaseGraphicsComponent.hpp"
#include "GraphicsComponentFactory.hpp"

BaseGraphicsComponent::BaseGraphicsComponent(const BaseGraphicsComponentData& rData)
{
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
