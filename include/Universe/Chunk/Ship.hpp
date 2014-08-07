#ifndef SHIP_H
#define SHIP_H

#include "Chunk.hpp"
#include "Decoration.hpp"

struct ShipData : public ChunkData//initialized
{
    ShipData() :
        ChunkData()
    {
        type = ClassType::SHIP;
        bodyType = b2BodyType::b2_dynamicBody;
        hullDecor.gfxCompData.texName = "textures/hull/kestral_2.png";
        hullDecor.gfxCompData.texTileSize = sf::Vector2f(652, 418);
        hullDecor.gfxCompData.gfxLayer = GraphicsLayer::ShipHull;
        hullDecor.gfxCompData.rotation = 90;
        hullDecor.gfxCompData.scale = sf::Vector2f(5,5);
        hullDecor.gfxCompData.color = sf::Color(255,255,255,255);
    }
    DecorationData hullDecor;
};

class Ship : public Chunk
{
public:
    Ship();
    Ship(const ShipData& rData);
    virtual ~Ship();

    virtual void draw();
protected:
private:
    virtual void f_initialize(const ShipData& rData);

    Decoration m_hullDecor;
};

#endif // SHIP_H
