#ifndef BASEGRAPHICSCOMPONENT_H
#define BASEGRAPHICSCOMPONENT_H

#include "stdafx.hpp"
#include "GraphicsLayer.hpp"
#include "Defaults.hpp"

class GraphicsComponentFactory;
struct BaseGraphicsComponentData;

class BaseGraphicsComponent/**PURE VIRTUAL**/
{
public:
    BaseGraphicsComponent(const BaseGraphicsComponentData& rData);
    virtual ~BaseGraphicsComponent();

    virtual const std::string& getTexName() const final;
    virtual GraphicsLayer getGfxLayer() const final;
    virtual void free() final;
    virtual void setVisibility(bool visible) final;
    virtual bool isVisible() const final;

    virtual void setPosition(const b2Vec2& rPos) = 0;
    virtual void setRotation(float radiansCCW) = 0;//radiansCCW
    virtual float getRotation() const = 0;//radiansCCW
    virtual void update() = 0;

    virtual void setVelocity(const b2Vec2& rVel);

    virtual void draw(sf::RenderTexture& rWindow, const b2Vec2& rCameraVel) final;
protected:
        virtual const sf::Drawable& getDrawable() const = 0;
private:
    b2Vec2 m_velVec;
    bool m_isVisible;
    GraphicsLayer m_gfxLayer;
    std::string m_texName;
    GraphicsComponentFactory* m_pFactoryParent;
};

struct BaseGraphicsComponentData
{
    BaseGraphicsComponentData() :
        dimensions(128, 128),
        startHidden(false),
        gfxLayer(defaults::graphics::layer),
        texName(defaults::graphics::texName),
        pParent(NULL)
    {

    }

    sf::Vector2f dimensions;
    bool startHidden;
    GraphicsLayer gfxLayer;
    std::string texName;
    GraphicsComponentFactory* pParent;

    virtual BaseGraphicsComponent* generate(GraphicsComponentFactory* parent) const
    {
        std::cout << "\nMAJOR ERROR: " << FILELINE << parent;
        ///ERROR LOG
        //BaseGraphicsComponentData mutableCopy(*this);
        //mutableCopy.pParent = parent;
        //return new BaseGraphicsComponent(mutableCopy);
        return NULL;
    }
};


#endif // BASEGRAPHICSCOMPONENT_H
