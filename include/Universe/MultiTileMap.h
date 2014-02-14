#ifndef MULTITILEMAP_H
#define MULTITILEMAP_H

#include <stdafx.h>
#include <Universe/DGModule.h>

struct texturedVertices
{
    sf::VertexArray vertices;
    sf::Texture* pTexture;
    std::string textureName;
    int nextAccessed;
};

class MultiTileMap : public sf::Drawable, public sf::Transformable
{
public:
    MultiTileMap() {m_tileSize = sf::Vector2i(64,64);}
    MultiTileMap(const sf::Vector2i& tileSize) {m_tileSize = tileSize;}

    void add(std::vector<GraphicsBase*> gBaseList);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2i m_tileSize;
    std::vector<std::tr1::shared_ptr<texturedVertices> > m_TexVertSPList;
    ///static TextureAllocator& m_rTexAlloc;
};

#endif // DCHUNK_H
