#include "GraphicsBase.h"
#include "globals.h"
#include "Rotate.h"

using namespace std;

GraphicsBase::GraphicsBase()
{
    GraphicsBaseData data;

    f_initialize(data, def::phys::halfSize, def::phys::offset, def::phys::rotation);
}
GraphicsBase::GraphicsBase(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset, const float rotation)
{
    f_initialize(rData, rHalfSize, rOffset, rotation);
}
GraphicsBase::~GraphicsBase()
{
}
void GraphicsBase::f_initialize(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset, const float rotation)
{
    m_animControl.setState(rData.animState);

    m_color = rData.color;
    m_tileHalfSize = sf::Vector2f(rHalfSize.x, rHalfSize.y);
    m_tilePos = sf::Vector2f(rOffset.x, rOffset.y);

    m_pVertex = NULL;
    m_texTileSize = rData.texTileSize;
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
void GraphicsBase::setTilePos(const sf::Vector2f& rTilePos)
{
    m_tilePos = rTilePos;//pointer
    m_pVertex = ((*m_pTextVertex)[m_textVertexIndex]);

    sf::Vector2f vertices[4];
    vertices[0] = sf::Vector2f(scale*(m_tilePos.x-m_tileHalfSize.x), scale*(m_tilePos.y-m_tileHalfSize.y));
    vertices[1] = sf::Vector2f(scale*(m_tilePos.x+m_tileHalfSize.x), scale*(m_tilePos.y-m_tileHalfSize.y));
    vertices[2] = sf::Vector2f(scale*(m_tilePos.x+m_tileHalfSize.x), scale*(m_tilePos.y+m_tileHalfSize.y));
    vertices[3] = sf::Vector2f(scale*(m_tilePos.x-m_tileHalfSize.x), scale*(m_tilePos.y+m_tileHalfSize.y));

    VertexData<sf::Vector2f> vdat = FindCenter(vertices, 4);
    RotateCoordinatesDegs(vertices, 4, m_netRotation, vdat.center);

    m_pVertex[0].position = vertices[0];
    m_pVertex[1].position = vertices[1];
    m_pVertex[2].position = vertices[2];
    m_pVertex[3].position = vertices[3];
}
const sf::Vector2f& GraphicsBase::getTilePosition() const
{
    return m_tilePos;
}
void GraphicsBase::incTexTile()///for testing only??? remove?
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
const sf::Vector2f& GraphicsBase::getTileHalfSize() const
{
    return m_tileHalfSize;
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
void GraphicsBase::animate()
{
    setTexTile(m_animControl.getTile());
}
AnimationController& GraphicsBase::getAnimationController()
{
    return m_animControl;
}
