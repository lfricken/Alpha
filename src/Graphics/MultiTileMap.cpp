#include "MultiTileMap.hpp"
#include "globals.hpp"
#include "Convert.hpp"

using namespace std;

MultiTileMap::MultiTileMap(const MultiTileMapData& rData) : BaseGraphicsComponent(static_cast<BaseGraphicsComponentData>(rData))
{

}
MultiTileMap::~MultiTileMap()
{

}
void MultiTileMap::draw(sf::RenderWindow& rWindow) const
{
    if(isVisible())
        rWindow.draw(*this);
}


/**
1. Figure out if one of our texVertices has the texture a gfxBase wants
2. if not make a new one with appropriate stuff
3. Add vertices to the list in texturedVertex
4. Give the gfxBase a pointer to to texturedVertex
5. Rinse Repeat
**/
void MultiTileMap::add(GraphicsBase* pGfxBase)
{
    std::vector<GraphicsBase*> miniList;
    miniList.push_back(pGfxBase);
    add(miniList);
}
void MultiTileMap::add(vector<GraphicsBase*>& rGfxBaseList)
{
    TexturedVertices* pTexturedVertex = NULL;
    for(auto it_gfxBase = rGfxBaseList.begin(); it_gfxBase != rGfxBaseList.end(); ++it_gfxBase)
    {
        bool found = false;
        for(auto it_texVert = m_TexVertSPList.begin(); it_texVert != m_TexVertSPList.end(); ++it_texVert)
        {
            /**1**/
            if((*it_texVert)->textureName == (*it_gfxBase)->getTexName())
            {
                found = true;
                pTexturedVertex = &**it_texVert;
            }
        }

        if(!found)/**2**/
        {
            m_TexVertSPList.push_back(tr1::shared_ptr<TexturedVertices>(new TexturedVertices));
            m_TexVertSPList.back()->pTexture = game.getTextureAllocator().request((*it_gfxBase)->getTexName());
            m_TexVertSPList.back()->textureName = (*it_gfxBase)->getTexName();
            m_TexVertSPList.back()->vertices.setPrimitiveType(sf::Quads);
            m_TexVertSPList.back()->nextAccessed = 0;

            pTexturedVertex = &*m_TexVertSPList.back();
        }

        /**3**/
        pTexturedVertex->vertices.resize(pTexturedVertex->vertices.getVertexCount()+4);//*4 because each one has 4 vertices/(quad)
        /**4**/
        (*it_gfxBase)->setTextVertex(pTexturedVertex, pTexturedVertex->nextAccessed);
        pTexturedVertex->nextAccessed += 4;//+= the number of vertices in sf::Quads!!!
    }
}
void MultiTileMap::setPosition(const b2Vec2& rPos)
{
    sf::Transformable::setPosition(leon::b2Tosf<float>(rPos));
}
void MultiTileMap::setRotation(float radiansCCW)//radians
{
    sf::Transformable::setRotation(-leon::radToDeg(radiansCCW));
}
void MultiTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(auto it_texVert = m_TexVertSPList.cbegin(); it_texVert != m_TexVertSPList.cend(); ++it_texVert)
    {
        states.texture = (*it_texVert)->pTexture;
        target.draw((*it_texVert)->vertices, states);
    }
}
void MultiTileMap::update()
{

}
