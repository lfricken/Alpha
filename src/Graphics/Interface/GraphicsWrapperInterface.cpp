#include "GraphicsWrapperInterface.hpp"

#include "BaseGraphicsComponent.hpp"

GraphicsWrapperInterface::GraphicsWrapperInterface()
{

}
GraphicsWrapperInterface::~GraphicsWrapperInterface()
{

}
void GraphicsWrapperInterface::setPosition(const b2Vec2& rPos)
{
    m_pGfxComp->setPosition(rPos);
}
void GraphicsWrapperInterface::setRotation(float radiansCCW)//radiansCCW
{
    m_pGfxComp->setRotation(radiansCCW);//radiansCCW
}
void GraphicsWrapperInterface::setVelocity(const b2Vec2& rVel)
{
    m_pGfxComp->setVelocity(rVel);
}
void GraphicsWrapperInterface::setColor(const sf::Color& rColor)
{
    std::cout << "\n" << FILELINE;
}
