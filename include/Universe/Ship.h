#ifndef SHIP_H
#define SHIP_H

#include "Chunk.h"
class ShipField;

struct ShipData
{
    ChunkData chunk;
};

class Ship : public Chunk
{
    public:
        Ship();
        Ship(ShipData& data);
        virtual ~Ship();

    protected:
    private:

};

#endif // SHIP_H
