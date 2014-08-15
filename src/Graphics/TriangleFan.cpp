#include "TriangleFan.h"

#include "Convert.hpp"
#include "Rotation.hpp"

using namespace sf;

TriangleFan::TriangleFan(const TriangleFanData& rData) : BaseGraphicsComponent(static_cast<BaseGraphicsComponentData>(rData))
{
    m_totalTexCoordRot = 0;
    sf::Transformable::setPosition(0,0);//just to make sure we have an owner and non NAN position

    m_texCoordCenterOffset = rData.textureCenterOffset;

    m_pTexture = game.getTextureAllocator().request(getTexName());
    m_vertices.setPrimitiveType(sf::TrianglesFan);
    m_vertices.resize(8);

    /**set local coordinates**/
    m_vertices[0].position = sf::Vector2f(0,0);
    m_vertices[1].position = sf::Vector2f(rData.dimensions.x/2, -2);
    m_vertices[2].position = sf::Vector2f(rData.dimensions.x/2, -rData.dimensions.y/2);
    m_vertices[3].position = sf::Vector2f(-rData.dimensions.x/2, -rData.dimensions.y/2);
    m_vertices[4].position = sf::Vector2f(-rData.dimensions.x/2, 0);
    m_vertices[5].position = sf::Vector2f(-rData.dimensions.x/2, rData.dimensions.y/2);
    m_vertices[6].position = sf::Vector2f(rData.dimensions.x/2, rData.dimensions.y/2);
    m_vertices[7].position = sf::Vector2f(rData.dimensions.x/2, 0);


    /**setTexture coordinates**/
    sf::Vector2f offset = m_texCoordCenterOffset;
    m_vertices[0].texCoords = sf::Vector2f(offset.x,offset.y);
    m_vertices[1].texCoords = sf::Vector2f(offset.x+rData.dimensions.x/2, offset.y+0);
    m_vertices[2].texCoords = sf::Vector2f(offset.x+rData.dimensions.x/2, offset.y+-rData.dimensions.y/2);
    m_vertices[3].texCoords = sf::Vector2f(offset.x+-rData.dimensions.x/2, offset.y+-rData.dimensions.y/2);
    m_vertices[4].texCoords = sf::Vector2f(offset.x+-rData.dimensions.x/2, offset.y+0);
    m_vertices[5].texCoords = sf::Vector2f(offset.x+-rData.dimensions.x/2, offset.y+rData.dimensions.y/2);
    m_vertices[6].texCoords = sf::Vector2f(offset.x+rData.dimensions.x/2, offset.y+rData.dimensions.y/2);
    m_vertices[7].texCoords = sf::Vector2f(offset.x+rData.dimensions.x/2, offset.y+0);


    /**COMPRESS THEM RADIALLY INTO THE BOTTOM HALF**/
    RotateCoordinatesRads(&m_vertices[1].texCoords, 1, leon::degToRad(-f_getRadialCompression(0)), offset);
    RotateCoordinatesRads(&m_vertices[2].texCoords, 1, leon::degToRad(-f_getRadialCompression(45)), offset);
    RotateCoordinatesRads(&m_vertices[3].texCoords, 1, leon::degToRad(-f_getRadialCompression(135)), offset);
    RotateCoordinatesRads(&m_vertices[4].texCoords, 1, leon::degToRad(-f_getRadialCompression(180)), offset);
    RotateCoordinatesRads(&m_vertices[5].texCoords, 1, leon::degToRad(-f_getRadialCompression(225)), offset);
    RotateCoordinatesRads(&m_vertices[6].texCoords, 1, leon::degToRad(-f_getRadialCompression(315)), offset);
    RotateCoordinatesRads(&m_vertices[7].texCoords, 1, leon::degToRad(-f_getRadialCompression(360)), offset);
}
TriangleFan::~TriangleFan()
{

}
void TriangleFan::rotateTexture(float radiansCCW)//radians
{
    radiansCCW *= 0.5;//because we should only rotate half as much because(obvious)

    m_totalTexCoordRot += radiansCCW;
    /**note that we will need to rotate the coordinates negative
    because of y axis change in texture coordinates**/
    /**hold the 0 coordinate still**/
    /**do a calculation for the new texture coords**/

    sf::Vector2f texCoordArray[8];
    for(unsigned int i = 0; i < 8; ++i)
        texCoordArray[i] = m_vertices[i].texCoords;

    /**this works because the rotation would have gone backwards, but is canceled out by
    the fact that texture coordinates y axis is flipped**/
    RotateCoordinatesRads(texCoordArray, 8, radiansCCW, sf::Vector2f(256,256));

    for(unsigned int i = 0; i < 8; ++i)
        m_vertices[i].texCoords = texCoordArray[i];
}
void TriangleFan::setTextureRotation(float radiansCCW)//radians
{
    rotateTexture(radiansCCW - 2*m_totalTexCoordRot);
}
void TriangleFan::draw(sf::RenderWindow& rWindow) const
{
    if(isVisible())
        rWindow.draw(*this);
}
void TriangleFan::setPosition(const b2Vec2& rPos)
{
    sf::Transformable::setPosition(leon::b2Tosf<float>(rPos));
}
void TriangleFan::setRotation(float radiansCCW)//radians
{
    sf::Transformable::setRotation(-leon::radToDeg(radiansCCW));
}
void TriangleFan::update()
{
    ///SHOULD ANYTHING BE HERE?
}
void TriangleFan::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
    states.texture = m_pTexture; // apply the texture// you may also override states.shader or states.blendMode if you want
    target.draw(m_vertices, states);// draw the vertex array
}
float TriangleFan::f_getRadialCompression(float degreesCCW)
{
    float compressionLevel = 0.5;
    float degreesInCircle = 360;

    return compressionLevel*(degreesInCircle-degreesCCW);
}
const sf::Drawable& TriangleFan::getDrawable() const
{
    return *this;
}
float TriangleFan::getRotation() const
{
    return leon::degToRad(sf::Transformable::getRotation());
}
