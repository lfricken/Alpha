#include "Projectile.h"
#include "globals.h"

using namespace std;

Projectile::Projectile() : Chunk()
{
    ProjectileData data;
    f_initialize(data);
}
Projectile::Projectile(const ProjectileData& sData) : Chunk(static_cast<ChunkData>(sData))
{
    f_initialize(sData);
}
Projectile::~Projectile()
{

}
void Projectile::f_initialize(const ProjectileData& data)
{
    m_damage = data.damage;
    m_projType = data.projType;
    m_pDamageFunc = game.getGameFunctionFinder().getFunction("damage");
}
void Projectile::setDamage(T_Damage damage)//set the damage this projectile will deal
{
    m_damage = damage;
}
ProjectileType Projectile::getProjType() const
{
    return m_projType;
}
void Projectile::endLife()
{
    game.getGameUniverse().getProjAlloc().recieveProjectile(this);
}
unsigned int Projectile::getListPos() const
{
    return m_listPosition;
}
void Projectile::setListPos(unsigned int pos)
{
    m_listPosition = pos;
}
void Projectile::swapListPos(Projectile& other)
{
    unsigned int temp = other.getListPos();
    other.setListPos(m_listPosition);
    setListPos(temp);
}
float Projectile::getLifeTimeRemain() const
{
    return m_lifeTimeRemaining;
}
void Projectile::setLifeTimeRemain(float time)
{
    m_lifeTimeRemaining = time;
}
float Projectile::changeLifeTimeRemain(float change)
{
    return (m_lifeTimeRemaining += change);
}

void Projectile::wake(const b2Vec2& pos, float angle, const b2Vec2& velocity, float angVel)//box2d uses radians
{
    Chunk::wake(pos, angle, velocity, angVel);
    disable();
}
int Projectile::startContact(PhysicsBase* other)
{
    /**do stuff**/
    cout << "\nType: " << other->getType();
    cout << "\nIs Solid: " << other->getButes().getBute(Butes::isSolid);
    if(other->getButes().getBute(Butes::isSolid))
    {
        sf::Packet damagePacket;
        damagePacket << m_damage;
        (*other.*m_pDamageFunc)(damagePacket);
        endLife();///put this in the above function!!! what?
    }

    return 0;
}
int Projectile::endContact(PhysicsBase* other)
{
    if(other->getType() == ClassType::HULL)
        enable();
}
void Projectile::enable()//no longer interacts with hull sensors, set to default collision state for a projectile
{
    for (b2Fixture* fix = m_pBody->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Filter filter = fix->GetFilterData();
        filter.maskBits = static_cast<uint16>(MaskBits::ProjectileNorm);
        fix->SetFilterData(filter);
    }
}
void Projectile::disable()//disable all collision except with hull sensors
{
    for (b2Fixture* fix = m_pBody->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Filter filter = fix->GetFilterData();
        filter.maskBits = static_cast<uint16>(MaskBits::ProjectileOff);
        fix->SetFilterData(filter);
    }
}
