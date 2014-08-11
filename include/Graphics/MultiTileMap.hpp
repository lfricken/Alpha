#ifndef MULTITILEMAP_H
#define MULTITILEMAP_H

#include "stdafx.hpp"
#include "GraphicsBase.hpp"
#include "BaseGraphicsComponent.hpp"

struct TexturedVertices
{
    sf::Vertex* operator[](const int access)
    {
        return &vertices[access];
    }
    sf::VertexArray vertices;
    sf::Texture* pTexture;
    std::string textureName;
    int nextAccessed;
};

struct MultiTileMapData;

class MultiTileMap : public sf::Drawable, public sf::Transformable, public BaseGraphicsComponent
{
public:
    MultiTileMap(const MultiTileMapData& rData);
    ~MultiTileMap();

    const sf::Drawable& getDrawable() const;

    void add(GraphicsBase* pGfxBase);
    void add(std::vector<GraphicsBase*>& gBaseList);

    void setPosition(const b2Vec2& rPos);
    void setRotation(float radiansCCW);//radians

    void update();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<std::tr1::shared_ptr<TexturedVertices> > m_TexVertSPList;
};

struct MultiTileMapData : public BaseGraphicsComponentData
{
    MultiTileMapData() :
        BaseGraphicsComponentData()
    {
        gfxLayer = GraphicsLayer::GModules;
    }

    virtual BaseGraphicsComponent* generate(GraphicsComponentFactory* parent) const
    {
        MultiTileMapData mutableCopy(*this);
        mutableCopy.pParent = parent;
        return new MultiTileMap(mutableCopy);
    }
};



#endif // DCHUNK_H


