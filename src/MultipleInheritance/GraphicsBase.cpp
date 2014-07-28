#include "GraphicsBase.h"
#include "globals.h"
#include "Rotate.h"

using namespace sf;

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
    m_tileHalfSize = rHalfSize;
    m_tilePos = rOffset;

    m_texTileSize = rData.texTileSize;
    m_texName = rData.texName;
    m_netRotation = rotation;
}

/**==============VERTICES=================**/
void GraphicsBase::setTextVertex(TexturedVertices* pTextVertex, const int index)
{
    m_textVertexIndex = index;
    m_pTextVertex = pTextVertex;

    setColor(m_color);
    setTexTile(m_texTile);
    setTilePos(m_tilePos);
}

/**==============TEXTURE*==============**/
void GraphicsBase::setTexTile(const sf::Vector2f& rTexTile)
{
    m_texTile = rTexTile;

    Vertex* pVertex = ((*m_pTextVertex)[m_textVertexIndex]);
    pVertex[0].texCoords = Vector2f(m_texTileSize.x*(m_texTile.x), m_texTileSize.y*(m_texTile.y+1));//bottom left(cartesian on the texture)
    pVertex[1].texCoords = Vector2f(m_texTileSize.x*(m_texTile.x+1), m_texTileSize.y*(m_texTile.y+1));
    pVertex[2].texCoords = Vector2f(m_texTileSize.x*(m_texTile.x+1), m_texTileSize.y*(m_texTile.y));
    pVertex[3].texCoords = Vector2f(m_texTileSize.x*(m_texTile.x), m_texTileSize.y*(m_texTile.y));//top left
}

/**==================WORLD TILE==============**/
void GraphicsBase::setTilePos(const b2Vec2& rTilePos)
{
    m_tilePos = rTilePos;
    Vertex* pVertex = ((*m_pTextVertex)[m_textVertexIndex]);

    Vector2f vertices[4];
    vertices[0] = leon::b2Tosf<float>(b2Vec2(m_tilePos.x-m_tileHalfSize.x, m_tilePos.y-m_tileHalfSize.y));//bottom left (cartesian in the world)
    vertices[1] = leon::b2Tosf<float>(b2Vec2(m_tilePos.x+m_tileHalfSize.x, m_tilePos.y-m_tileHalfSize.y));//bottom right
    vertices[2] = leon::b2Tosf<float>(b2Vec2(m_tilePos.x+m_tileHalfSize.x, m_tilePos.y+m_tileHalfSize.y));//top right
    vertices[3] = leon::b2Tosf<float>(b2Vec2(m_tilePos.x-m_tileHalfSize.x, m_tilePos.y+m_tileHalfSize.y));//top left

    VertexData<Vector2f> vdat = FindCenter(vertices, 4);
    RotateCoordinatesDegs(vertices, 4, m_netRotation, vdat.center);

    pVertex[0].position = vertices[0];
    pVertex[1].position = vertices[1];
    pVertex[2].position = vertices[2];
    pVertex[3].position = vertices[3];
}

/**==================OTHER==================**/
void GraphicsBase::setColor(const sf::Color& rColor)
{
    m_color = rColor;

    Vertex* pVertex = ((*m_pTextVertex)[m_textVertexIndex]);

    pVertex[0].color = rColor;
    pVertex[1].color = rColor;
    pVertex[2].color = rColor;
    pVertex[3].color = rColor;
}
const std::string& GraphicsBase::getTexName() const
{
    return m_texName;
}
AnimationController& GraphicsBase::getAnimationController()
{
    return m_animControl;
}

void GraphicsBase::animate()
{
    setTexTile(m_animControl.getTile());
}
