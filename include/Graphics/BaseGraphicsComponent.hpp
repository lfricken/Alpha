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
    virtual void setRotation(float radiansCCW) = 0;//radians

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& rWindow) const = 0;
protected:
private:
    bool m_isVisible;
    GraphicsLayer m_gfxLayer;
    std::string m_texName;
    GraphicsComponentFactory* m_pFactoryParent;
};

struct BaseGraphicsComponentData
{
    BaseGraphicsComponentData() :
        startHidden(false),
        gfxLayer(defaults::graphics::layer),
        texName(defaults::graphics::texName),
        pParent(NULL)
    {

    }

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
