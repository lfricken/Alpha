#include "GraphicsComponent.hpp"

#include "globals.hpp"
#include "GraphicsComponentFactory.hpp"
#include "Convert.hpp"


GraphicsComponent::GraphicsComponent(const GraphicsComponentData& rData) : BaseGraphicsComponent(static_cast<BaseGraphicsComponentData>(rData))
{

    m_rotation = rData.rotation;

    m_animControl.load(rData.animationFileName);
    m_texTileSize = m_animControl.getTexTileSize();

    m_sprite.setOrigin(m_texTileSize.x/2.0f, m_texTileSize.y/2.0f);
    m_sprite.setTexture(*game.getTextureAllocator().request(getTexName()), false);

    sf::Vector2f scale;
    if(rData.dimensions != sf::Vector2f(0,0))
    {
        scale.x = rData.dimensions.x/m_texTileSize.x;
        scale.y = rData.dimensions.y/m_texTileSize.y;
    }
    else
        scale = sf::Vector2f(1,1);

    m_sprite.setScale(scale);
    m_sprite.setColor(rData.color);

    setPosition(b2Vec2(rData.position.x, rData.position.y));
    m_animControl.setState(rData.animState);
}
GraphicsComponent::~GraphicsComponent()
{

}
void GraphicsComponent::setPosition(const b2Vec2& rPos)
{
    m_sprite.setPosition(leon::b2Tosf<float>(rPos));
}
void GraphicsComponent::setRotation(float radiansCCW)
{
    m_sprite.setRotation(leon::radToDeg(-radiansCCW)-m_rotation);
}
sf::Sprite& GraphicsComponent::getSprite()
{
    return m_sprite;
}
void GraphicsComponent::setAnimState(AnimationState state)
{
    if(m_animControl.getState() != state)
        m_animControl.setState(state);
    else
        m_animControl.goAgain(true);
}
void GraphicsComponent::update()
{
    sf::Vector2f topLeftCoord = m_animControl.getTile();
    sf::IntRect texRect(topLeftCoord.x*m_texTileSize.x, topLeftCoord.y*m_texTileSize.y, m_texTileSize.x, m_texTileSize.y);//left most, right most, width, height
    m_sprite.setTextureRect(texRect);
}
const sf::Drawable& GraphicsComponent::getDrawable() const
{
    return m_sprite;
}
float GraphicsComponent::getRotation() const
{
    return leon::degToRad(m_sprite.getRotation());
}

