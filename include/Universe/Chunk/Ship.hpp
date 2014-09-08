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
        hullDecor.gfxCompData.texName = "textures/hull/loahn.png";
        hullDecor.gfxCompData.animationFileName = "textures/hull/loahn.acfg";
        hullDecor.gfxCompData.gfxLayer = GraphicsLayer::ShipHull;
        hullDecor.gfxCompData.rotation = 0;
        hullDecor.gfxCompData.scale = sf::Vector2f(4,4);
        //hullDecor.gfxCompData.color = sf::Color(255,255,255,255);
    }
    DecorationData hullDecor;
};

class Ship : public Chunk
{
public:
    Ship();
    Ship(const ShipData& rData);
    virtual ~Ship();

    virtual void gfxUpdate();
protected:
private:

    Decoration m_hullDecor;
};

#endif // SHIP_H
