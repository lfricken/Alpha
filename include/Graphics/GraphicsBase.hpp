#ifndef GRAPHICSBASE_H
#define GRAPHICSBASE_H

#include "stdafx.hpp"
#include "IOBase.hpp"
#include "AnimationController.hpp"
#include "AnimationState.hpp"

struct TexturedVertices;

struct GraphicsBaseData//initialized
{
    GraphicsBaseData() :
        animationFileName(defaults::graphics::animFile),
        texName(defaults::graphics::texName),
        color(defaults::graphics::color),
        texTileSize(defaults::graphics::texTileSize),
        animState(defaults::graphics::animState)
        {}

    std::string animationFileName;
    std::string texName;
    sf::Color color;//color mask
    sf::Vector2f texTileSize;//size of the texture rectangle
    AnimationState animState;//sets animation to start initially or not

};


class GraphicsBase
{
public:
    GraphicsBase();
    GraphicsBase(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset, const float rotation);
    virtual ~GraphicsBase();

    /**VERTICES**/
    void setTextVertex(TexturedVertices* pTextVertex, const int index);

    /**TEXTURE**/
    void setTexTile(const sf::Vector2f& rTexTile);//position of the display tile on the texture

    /**WORLD TILE**/
    void setTilePos(const b2Vec2& rTilePos);//position of tile in the tilemap

    /**OTHER**/
    void setColor(const sf::Color& rColor);//set color of the vertices
    const std::string& getTexName() const;

    AnimationController& getAnimationController();
    void animate();
protected:
private:
    virtual void f_initialize(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset, const float rotation);

    /**VERTICES**/
    TexturedVertices* m_pTextVertex;//pointer to the beginning of the vertices
    int m_textVertexIndex;//how far down the list of textured vertices our vertices are

    /**TEXTURE**/
    sf::Vector2f m_texTileSize;//size of tile that is displaying from the texture
    sf::Vector2f m_texTile;//tile of the texture that is being displayed

    /**WORLD TILE**/
    b2Vec2 m_tileHalfSize;//size of us in world coords
    b2Vec2 m_tilePos;//position of the tile in the map

    /**OTHER**/
    sf::Color m_color;//color modifier for the vertices, needs to be stored because our vertexes don't exist when we are created
    float m_netRotation;
    std::string m_texName;

    AnimationController m_animControl;
};

#endif // GRAPHICSBASE_H
