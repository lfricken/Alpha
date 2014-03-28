#include "Ship.h"
///#include "ShipField.h"
#include "ForceField.h"

using namespace std;

Ship::Ship() : Chunk()
{
    ShipData data;
    f_initialize(data);
}
Ship::Ship(const ShipData& sData) : Chunk(static_cast<ChunkData>(sData))
{
    f_initialize(sData);
}
Ship::~Ship()
{

}
void Ship::f_initialize(const ShipData& sData)
{
    ForceFieldData data;
    data.shape = Shape::Circle;
    data.isSensor = true;
    data.halfSize = b2Vec2(4, 4);
    data.density = 0;
    data.pBody = m_pBody;
    data.categoryBits = CollisionCategory::Sensor;
    data.maskBits = CollisionCategory::Projectile | CollisionCategory::Sensor;

    ForceField* tempPtr = new ForceField(data);
    m_ModuleSPList.push_back(tr1::shared_ptr<Module>(tempPtr));
    m_SpecialPhysPList.push_back(tempPtr);
}
