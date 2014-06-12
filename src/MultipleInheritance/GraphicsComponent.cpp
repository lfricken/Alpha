#include "GraphicsComponent.h"

#include "globals.h"

GraphicsComponent::GraphicsComponent()
{
    GraphicsComponentData data;
    f_init(data);
}
GraphicsComponent::GraphicsComponent(const GraphicsComponentData& rData)
{
    f_init(rData);
}
GraphicsComponent::~GraphicsComponent()
{

}
void GraphicsComponent::f_init(const GraphicsComponentData& rData)
{
    m_sprite.setTexture(*game.getTextureAllocator().request(rData.texName), false);

    m_texTileSize = rData.texTileSize;
    m_texTileSize = rData.texTileSize;

    m_sprite.setScale(rData.scale);
    m_sprite.setColor(rData.color);
    m_sprite.setPosition(rData.position);
}
void GraphicsComponent::load(const std::string& sheet)
{
    ///do this
    /**load the texture along with the animation stuff to be sent to animationController**/
    ///m_texTileSize.x = load;
    ///m_texTileSize.y = load;
    m_sprite.setTexture(*game.getTextureAllocator().request(sheet), false);
}
const sf::Sprite& GraphicsComponent::getSprite() const
{
    return m_sprite;
}
void GraphicsComponent::setPosition(const sf::Vector2f& pos)
{
    m_sprite.setPosition(pos);
}
void GraphicsComponent::move(const sf::Vector2f& change)
{
    m_sprite.move(change);
}
void GraphicsComponent::setRotation(float r)
{
    m_sprite.setRotation(r);
}
void GraphicsComponent::rotate(float r)
{
    m_sprite.rotate(r);
}
void GraphicsComponent::f_update()
{
    sf::Vector2f topLeftCoord = m_animControl.getTile();
    sf::IntRect texRect(topLeftCoord.x*m_texTileSize.x, topLeftCoord.y*m_texTileSize.y, m_texTileSize.x, m_texTileSize.y);//left most, right most, width, height
    m_sprite.setTextureRect(texRect);
}
