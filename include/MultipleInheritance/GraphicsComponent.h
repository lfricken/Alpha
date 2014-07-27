#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "defaults.h"
#include "stdafx.h"

#include "AnimationController.h"
#include "GraphicsLayer.h"
class GraphicsComponentFactory;

struct GraphicsComponentData
{
    GraphicsComponentData() :
        animState(def::gfx::animState),
        position(def::gfx::position),
        rotation(def::gfx::rotation),
        scale(def::gfx::scale),
        texTileSize(def::gfx::texTileSize),
        color(def::gfx::color),
        texName(def::gfx::texName),
        pParent(NULL),
        gfxLayer(def::gfx::layer)
    {
    }

    AnimationState animState;
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
    sf::Vector2f texTileSize;
    sf::Color color;
    std::string texName;

    GraphicsComponentFactory* pParent;
    GraphicsLayer gfxLayer;
};

class GraphicsComponent
{
public:
    GraphicsComponent();
    GraphicsComponent(const GraphicsComponentData& rData);
    virtual ~GraphicsComponent();

    void load(const std::string& sheet);

    const sf::Sprite& getSprite() const;//to be used for drawing, a function calls this and tells window to draw it
    const std::string& getTexName() const;
    GraphicsLayer getGfxLayer() const;

    void setPosition(const b2Vec2& rPos);
    void setRotation(float r);
    void setAnimState(AnimationState state);

    void free();
    void update();
protected:
private:
    virtual void f_init(const GraphicsComponentData& rData);

    std::string m_texName;
    GraphicsComponentFactory* m_pParent;
    GraphicsLayer m_gfxLayer;

    sf::Vector2f m_texTileSize;

    AnimationController m_animControl;
    sf::Sprite m_sprite;/**if we need to, we can make another class that gives out a vertex quad and keeps them in a bunch of buffers and draws them**/
    float m_rotation;
};

#endif // GRAPHICSCOMPONENT_H
