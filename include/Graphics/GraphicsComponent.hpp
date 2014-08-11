#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Defaults.hpp"
#include "stdafx.hpp"

#include "AnimationController.hpp"
#include "GraphicsLayer.hpp"
class GraphicsComponentFactory;

struct GraphicsComponentData
{
    GraphicsComponentData() :
        animState(defaults::graphics::animState),
        position(defaults::graphics::position),
        rotation(defaults::graphics::rotation),//degrees CCW
        scale(defaults::graphics::scale),
        texTileSize(defaults::graphics::texTileSize),
        color(defaults::graphics::color),
        texName(defaults::graphics::texName),
        animationFileName(defaults::graphics::animFile),
        pParent(NULL),
        gfxLayer(defaults::graphics::layer)
    {
    }

    AnimationState animState;
    sf::Vector2f position;
    float rotation;//degrees CCW
    sf::Vector2f scale;
    sf::Vector2f texTileSize;
    sf::Color color;
    std::string texName;
    std::string animationFileName;

    GraphicsComponentFactory* pParent;
    GraphicsLayer gfxLayer;
};

class GraphicsComponent
{
public:
    GraphicsComponent(const GraphicsComponentData& rData, GraphicsComponentFactory* pFactory);
    virtual ~GraphicsComponent();

    const sf::Sprite& getSprite() const;//to be used for drawing, a function calls this and tells window to draw it
    const std::string& getTexName() const;
    GraphicsLayer getGfxLayer() const;

    void setPosition(const b2Vec2& rPos);
    void setRotation(float radiansCCW);//radians
    void setAnimState(AnimationState state);

    void free();
    void update();
protected:
private:

    std::string m_texName;
    GraphicsComponentFactory* m_pParent;
    GraphicsLayer m_gfxLayer;

    sf::Vector2f m_texTileSize;

    AnimationController m_animControl;
    sf::Sprite m_sprite;/**if we need to, we can make another class that gives out a vertex quad and keeps them in a bunch of buffers and draws them**/
    float m_rotation;//degrees
};

#endif // GRAPHICSCOMPONENT_H
