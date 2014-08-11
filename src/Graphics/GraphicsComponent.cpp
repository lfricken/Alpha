#include "GraphicsComponent.hpp"

#include "globals.hpp"
#include "GraphicsComponentFactory.hpp"
#include "Convert.hpp"


GraphicsComponent::GraphicsComponent(const GraphicsComponentData& rData, GraphicsComponentFactory* pFactory)
{
    m_texName = rData.texName;

    m_sprite.setOrigin(rData.texTileSize.x/2, rData.texTileSize.y/2);
    m_texTileSize = rData.texTileSize;
    m_sprite.setTexture(*game.getTextureAllocator().request(m_texName), false);
    m_rotation = rData.rotation;

    m_sprite.setScale(rData.scale);
    m_sprite.setColor(rData.color);


    m_gfxLayer = rData.gfxLayer;
    m_pParent = pFactory;

    setPosition(b2Vec2(rData.position.x, rData.position.y));
    m_animControl.load(rData.animationFileName);
    m_animControl.setState(rData.animState);
}
GraphicsComponent::~GraphicsComponent()
{

}
const sf::Sprite& GraphicsComponent::getSprite() const
{
    return m_sprite;
}
const std::string& GraphicsComponent::getTexName() const
{
    return m_texName;
}
GraphicsLayer GraphicsComponent::getGfxLayer() const
{
    return m_gfxLayer;
}
void GraphicsComponent::setPosition(const b2Vec2& rPos)
{
    m_sprite.setPosition(leon::b2Tosf<float>(rPos));
}
void GraphicsComponent::setRotation(float radiansCCW)
{
    m_sprite.setRotation(leon::radToDeg(-radiansCCW)-m_rotation);
}
void GraphicsComponent::setAnimState(AnimationState state)
{
    m_animControl.setState(state);
}
void GraphicsComponent::free()
{
    m_pParent->freeComponent(this);
}
void GraphicsComponent::update()
{
    sf::Vector2f topLeftCoord = m_animControl.getTile();
    sf::IntRect texRect(topLeftCoord.x*m_texTileSize.x, topLeftCoord.y*m_texTileSize.y, m_texTileSize.x, m_texTileSize.y);//left most, right most, width, height
    m_sprite.setTextureRect(texRect);
}
