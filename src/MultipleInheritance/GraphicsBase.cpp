#include "GraphicsBase.h"
#include "globals.h"
#include "Rotate.h"

using namespace std;

GraphicsBase::GraphicsBase()
{
    GraphicsBaseData data;

    f_initialize(data, def::phys::defaultHalfSize, def::phys::defaultOffset, def::phys::defaultRotation);
}
GraphicsBase::GraphicsBase(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset, const float rotation)
{
    f_initialize(rData, rHalfSize, rOffset, rotation);
}
GraphicsBase::~GraphicsBase()
{
}
///    : m_color(rData.color), m_tileSize(rHalfSize.x*2, rHalfSize.y*2), m_tilePos(rOffset.x, rOffset.y)
void GraphicsBase::f_initialize(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset, const float rotation)
{
    m_color = rData.color;
    m_tileSize = sf::Vector2f(rHalfSize.x*2, rHalfSize.y*2);
    m_tilePos = sf::Vector2f(rOffset.x, rOffset.y);///IS M_TILEPOS CORRECTLY SET?

    m_pVertex = NULL;
    m_texTileSize = rData.texTileSize;
    m_texTile = rData.texTile;
    m_texName = rData.texName;
    m_netRotation = rotation;
}
void GraphicsBase::setTexName(const string& texName)
{
    m_texName = texName;///UPDATE OUR TEXTURE????
}
const string GraphicsBase::getTexName() const
{
    return m_texName;
}
void GraphicsBase::setVertex(sf::Vertex* pVertex)///verify pointer integrity
{
    m_pVertex = pVertex;
    setColor(m_color);
    setTexTile(m_texTile);
    setTilePos(m_tilePos);
}
const sf::Vertex* GraphicsBase::getVertex() const///verify pointer integrity??
{
    return ((*m_pTextVertex)[m_textVertexIndex]);
}
void GraphicsBase::setTextVertex(TexturedVertices* pTextVertex, const int index)
{
    m_textVertexIndex = index;
    m_pTextVertex = pTextVertex;

    m_pVertex = ((*m_pTextVertex)[m_textVertexIndex]);
    setColor(m_color);
    setTexTile(m_texTile);
    setTilePos(m_tilePos);
}
const TexturedVertices* GraphicsBase::getTextVertex() const
{
    return m_pTextVertex;
}
int GraphicsBase::getTextVertexIndex() const
{
    return m_textVertexIndex;
}




void GraphicsBase::setTilePos(const sf::Vector2f& rTilePos)/**///THIS IS GOING WRONG SOMEHOW, or is it?
{
    m_tilePos = rTilePos;//pointer
        ///make this use the tex vert pointer
    m_pVertex = ((*m_pTextVertex)[m_textVertexIndex]);

    sf::Vector2f vertices[4];
    vertices[0] = sf::Vector2f(scale*m_tilePos.x, scale*m_tilePos.y);
    vertices[1] = sf::Vector2f(scale*(m_tilePos.x+m_tileSize.x), scale*m_tilePos.y);//1
    vertices[2] = sf::Vector2f(scale*(m_tilePos.x+m_tileSize.x), scale*(m_tilePos.y+m_tileSize.y));//2
    vertices[3] = sf::Vector2f(scale*m_tilePos.x, scale*(m_tilePos.y+m_tileSize.y));//3

    RotateCoordinatesDegs(vertices, 4, m_netRotation, FindCenter(vertices, 4));

    m_pVertex[0].position = vertices[0];
    m_pVertex[1].position = vertices[1];
    m_pVertex[2].position = vertices[2];
    m_pVertex[3].position = vertices[3];
}
const sf::Vector2f& GraphicsBase::getTilePosition() const///nomenclature
{
    return m_tilePos;
}
void GraphicsBase::incTexTile()///for testing???
{
    if(m_texTile.x == 3)
        m_texTile.x = 0;
    else
        m_texTile.x += 1;
    setTexTile(m_texTile);
}
void GraphicsBase::setTexTile(const sf::Vector2f& rTexTile)/**set texture tile in our loaded graphic**/
{
    m_texTile = rTexTile;//pointer
        ///make this use the tex vert pointer
    m_pVertex = ((*m_pTextVertex)[m_textVertexIndex]);
    m_pVertex[0].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x), m_texTileSize.y*(m_texTile.y));
    m_pVertex[1].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x+1), m_texTileSize.y*(m_texTile.y));
    m_pVertex[2].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x+1), m_texTileSize.y*(m_texTile.y+1));
    m_pVertex[3].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x), m_texTileSize.y*(m_texTile.y+1));
}
const sf::Vector2f& GraphicsBase::getTexTile() const
{
    return m_texTile;
}
void GraphicsBase::setTileSize(const sf::Vector2f& rTileSize)
{
    m_tileSize = rTileSize;
    setTexTile(m_texTile);
    setTilePos(m_tilePos);
}
const sf::Vector2f& GraphicsBase::getTileSize() const
{
    return m_tileSize;
}
void GraphicsBase::setColor(const sf::Color& rColor)
{
    m_color = rColor;//pointer
    ///make this use the tex vert pointer
    m_pVertex = ((*m_pTextVertex)[m_textVertexIndex]);

    m_pVertex[0].color = rColor;
    m_pVertex[1].color = rColor;
    m_pVertex[2].color = rColor;
    m_pVertex[3].color = rColor;
}
const sf::Color& GraphicsBase::getColor()
{
    m_pVertex = ((*m_pTextVertex)[m_textVertexIndex]);
    return m_pVertex[0].color;//pointer
}
/*
void GraphicsBase::setDispPri(const int dispPri)
{
    m_dispPri = dispPri;
}
const int GraphicsBase::getDispPri() const
{
    return m_dispPri;
}
*/
/**Const Overloads**/
