#ifndef MULTITILEMAP_H
#define MULTITILEMAP_H

#include "stdafx.h"
#include "GraphicsBase.h"

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

class MultiTileMap : public sf::Drawable, public sf::Transformable
{
public:
    MultiTileMap();
    MultiTileMap(const MultiTileMap& old);
    MultiTileMap& operator= (const MultiTileMap& other);
    ~MultiTileMap();

    void add(GraphicsBase* pGfxBase);
    void add(std::vector<GraphicsBase*>& gBaseList);

    /**CONST OVERLOADS**/
    const sf::Vector2i& getTileSize() const;
    const std::vector<std::tr1::shared_ptr<TexturedVertices> >& getTexVertList() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /*sf::Vector2i m_tileSize;*/
    std::vector<std::tr1::shared_ptr<TexturedVertices> > m_TexVertSPList;
};

#endif // DCHUNK_H
