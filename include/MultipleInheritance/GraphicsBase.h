#ifndef GRAPHICSBASE_H
#define GRAPHICSBASE_H

#include "stdafx.h"
#include "IOBase.h"

struct GraphicsBaseData
{
    std::string texName;/**graphics**/
    sf::Color color;//color mask
    sf::Vector2f texTileSize;//size of the texture rectangle
    sf::Vector2f texTile;//texture tile that needs to be displayed
};

///Maybe we shouldn't have so many setters, getters are ok
class GraphicsBase///http://stackoverflow.com/questions/14399929/should-i-use-public-or-private-variables
///read first post
{
public:
    GraphicsBase(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset);
    virtual ~GraphicsBase();

    virtual bool graphicsInput(Package& rPackage);/**returns true if it got called**/

    virtual void setTexName(const std::string& rTexName);
    virtual const std::string getTexName() const;

    virtual void setVertex(sf::Vertex* pVertex);
    virtual const sf::Vertex* getVertex() const;

    virtual void setTilePos(const sf::Vector2f& rTilePos);
    virtual const sf::Vector2f& getTilePosition() const;

    virtual void incTexTile();

    virtual void setTexTile(const sf::Vector2f& rTexTile);
    virtual const sf::Vector2f& getTexTile() const;

    virtual void setTileSize(const sf::Vector2f& rTileSize);
    virtual const sf::Vector2f& getTileSize() const;

    virtual void setColor(const sf::Color& rColor);
    virtual const sf::Color& getColor() const;

    virtual void setDispPri(const int dispPri);
    virtual const int getDispPri() const;
protected:
    sf::Color m_color;//color modifier for the vertices
    sf::Vector2f m_tileSize;//size of pos coords
    sf::Vector2f m_texTileSize;//size of tex coords
    sf::Vector2f m_texTile;//tile of the texture that is being displayed
    sf::Vector2f m_tilePos;//position of the tile


    int m_dispPri;///display priority, has it been implemented?
    sf::Vertex* m_pVertex;/**never go above 3rd index,because we only have our own set of 4 vertices**/
    std::string m_texName;
private:
};

#endif // GRAPHICSBASE_H
