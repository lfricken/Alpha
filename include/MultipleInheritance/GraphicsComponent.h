#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "defaults.h"
#include "stdafx.h"

#include "AnimationController.h"



struct GraphicsComponentData
{
    GraphicsComponentData() :
        position(def::gfx::position),
        rotation(def::gfx::rotation),
        scale(def::gfx::scale),
        texTileSize(def::gfx::texTileSize),
        color(def::gfx::color),
        texName(def::gfx::texName) {}

    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
    sf::Vector2f texTileSize;
    sf::Color color;
    std::string texName;
};

class GraphicsComponent
{
public:
    GraphicsComponent();
    GraphicsComponent(const GraphicsComponentData& rData);
    virtual ~GraphicsComponent();

    void load(const std::string& sheet);

    const sf::Sprite& getSprite() const;//to be used for drawing, a function calls this and tells window to draw it

    void setPosition(const sf::Vector2f& pos);
    void move(const sf::Vector2f& change);

    void setRotation(float r);
    void rotate(float r);

protected:
private:
    virtual void f_init(const GraphicsComponentData& rData);
    virtual void f_update();

    sf::Vector2f m_texTileSize;

    AnimationController m_animControl;
    sf::Sprite m_sprite;/**if we need to, we can make another class that gives out a vertex quad and keeps them in a bunch of buffers and draws them**/
};

#endif // GRAPHICSCOMPONENT_H
