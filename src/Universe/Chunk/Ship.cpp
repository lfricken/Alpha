#include "Ship.hpp"
#include "ForceField.hpp"

using namespace std;

Ship::Ship(const ShipData& rData) : Chunk(static_cast<ChunkData>(rData)), m_hullDecor(rData.hullDecor)
{

}
Ship::~Ship()
{

}
void Ship::gfxUpdate()
{
    m_hullDecor.setPosition(m_pBody->GetPosition());
    m_hullDecor.setRotation(m_pBody->GetAngle());
    m_hullDecor.setVelocity(m_pBody->GetLinearVelocity());
    Chunk::gfxUpdate();
}
