#include "Ship.h"
///#include "ShipField.h"
#include "ForceField.h"

using namespace std;

Ship::Ship()
{
    ForceFieldData data;
    data.moduleBaseData.physicsData.shape = PhysicsBaseData::Circle;
   // data.moduleBaseData.physicsData.isSensor = true;
    data.moduleBaseData.physicsData.halfSize = b2Vec2(8,8);
    data.moduleBaseData.physicsData.density = 0;
    data.moduleBaseData.physicsData.pBody = m_pBody;
    data.moduleBaseData.physicsData.categoryBits = CollisionCategory::Sensor;
    data.moduleBaseData.physicsData.maskBits = CollisionCategory::Projectile | CollisionCategory::Sensor;

    ForceField* tempPtr = new ForceField(data);
    m_ModuleSPList.push_back(tr1::shared_ptr<Module>(tempPtr));
    m_SpecialPhysPList.push_back(tempPtr);
  //  m_spShipField = tr1::shared_ptr<ShipField>(new ShipField(this));
  //  m_spShipField->setup();
}
Ship::Ship(ShipData& sData) : Chunk(sData.chunk)
{
    ForceFieldData data;
    data.moduleBaseData.physicsData.shape = PhysicsBaseData::Circle;
 //   data.moduleBaseData.physicsData.isSensor = true;
    data.moduleBaseData.physicsData.halfSize = b2Vec2(8,8);
    data.moduleBaseData.physicsData.density = 0;
    data.moduleBaseData.physicsData.pBody = m_pBody;


    ForceField* tempPtr = new ForceField(data);
    m_ModuleSPList.push_back(tr1::shared_ptr<Module>(tempPtr));
    m_SpecialPhysPList.push_back(tempPtr);

  //  m_spShipField = tr1::shared_ptr<ShipField>(new ShipField(this));
   // m_spShipField->setup();
}
Ship::~Ship()
{

}
