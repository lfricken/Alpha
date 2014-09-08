#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Defaults.hpp"
#include "stdafx.hpp"

#include "AnimationController.hpp"
#include "BaseGraphicsComponent.hpp"

class GraphicsComponentFactory;

struct GraphicsComponentData;

class GraphicsComponent : public BaseGraphicsComponent
{
public:
    GraphicsComponent(const GraphicsComponentData& rData);
    virtual ~GraphicsComponent();

    void setPosition(const b2Vec2& rPos);
    void setRotation(float radiansCCW);//radians
    float getRotation() const;///WARNING, THIS RETURNS SPRITE ABSOLUTE ROTATION(INCLUDES INIT OFFSET)
    void setAnimState(AnimationState state);

    void update();
protected:
private:
    const sf::Drawable& getDrawable() const;
    sf::Vector2f m_texTileSize;

    AnimationController m_animControl;
    sf::Sprite m_sprite;/**if we need to, we can make another class that gives out a vertex quad and keeps them in a bunch of buffers and draws them**/
    float m_rotation;///degrees???
};


struct GraphicsComponentData : public BaseGraphicsComponentData
{
    GraphicsComponentData() :
        BaseGraphicsComponentData(),
        animState(defaults::graphics::animState),
        position(defaults::graphics::position),
        rotation(defaults::graphics::rotation),//degrees CCW
        scale(defaults::graphics::scale),
        color(defaults::graphics::color),
        animationFileName(defaults::graphics::animFile)
    {

    }

    AnimationState animState;
    sf::Vector2f position;
    float rotation;//degrees CCW
    sf::Vector2f scale;
    sf::Color color;
    std::string animationFileName;



    virtual BaseGraphicsComponent* generate(GraphicsComponentFactory* parent) const
    {
        GraphicsComponentData mutableCopy(*this);
        mutableCopy.pParent = parent;
        return new GraphicsComponent(mutableCopy);
    }
};

#endif // GRAPHICSCOMPONENT_H
