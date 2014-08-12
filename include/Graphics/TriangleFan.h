#ifndef TRIANGLEFAN_H
#define TRIANGLEFAN_H

#include <BaseGraphicsComponent.hpp>
struct TriangleFanData;

class TriangleFan : public sf::Drawable, public sf::Transformable, public BaseGraphicsComponent
{
public:
    TriangleFan(const TriangleFanData& rData);
    virtual ~TriangleFan();

    void rotateTexture(float radiansCCW);//radiansCCW
    void setTextureRotation(float radiansCCW);//radiansCCW

    void draw(sf::RenderWindow& rWindow) const;
    void setPosition(const b2Vec2& rPos);
    void setRotation(float radiansCCW);//radians
    void update();

protected:
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float f_getRadialCompressionAmount(float degreesCCW);//figures out how much to

    const sf::Texture* m_pTexture;//make sure we don't modify the texture
    float m_totalTexCoordRot;//radians CCW
    sf::VertexArray m_vertices;
};



struct TriangleFanData : public BaseGraphicsComponentData
{
    TriangleFanData() :
        BaseGraphicsComponentData(),
        dimensions(128, 128)
    {
        gfxLayer = GraphicsLayer::BackgroundClose;
        texName = "textures/fill/orange.png";
    }

    sf::Vector2f dimensions;

    virtual BaseGraphicsComponent* generate(GraphicsComponentFactory* factory) const
    {
        TriangleFanData mutableCopy(*this);
        mutableCopy.pParent = factory;
        return new TriangleFan(mutableCopy);
    }
};

#endif // TRIANGLEFAN_H
