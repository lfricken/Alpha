#include "Ship.hpp"
///#include "ShipField.hpp"
#include "ForceField.hpp"

using namespace std;


Ship::Ship(const ShipData& sData) : Chunk(static_cast<ChunkData>(sData))
{
    f_initialize(sData);
}
Ship::~Ship()
{

}
void Ship::f_initialize(const ShipData& sData)
{

}
