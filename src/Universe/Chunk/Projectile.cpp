#include "Projectile.hpp"

#include "globals.hpp"
#include "IOManager.hpp"
#include "PhysicsBase.hpp"

using namespace std;


Projectile::Projectile(const ProjectileData& rData) : Chunk(static_cast<ChunkData>(rData))
{
    m_projType = rData.projType;

    //Damage Package:
    sf::Packet damagePacket;
    T_Damage damage = rData.damage;
    damagePacket << damage;
    m_damagePackage.reset("", "damage", damagePacket, 0.0f, Destination::UNIVERSE, false);
}
Projectile::~Projectile()
{

}
void Projectile::setDamage(T_Damage damage)//set the damage this projectile will deal
{
    sf::Packet damagePacket;
    damagePacket << damage;
    m_damagePackage.setParameter(damagePacket);
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
    //std::cout << "\nStart Projectile Contact";
    /**do stuff**/
    if(other->getButes().getBute(Butes::isSolid))
    {
        m_damagePackage.setTargetName(other->getName());
        m_damagePackage.setTargetID(other->getID());
        game.getGameIOManager().recieve(m_damagePackage);
        endLife();///put this in the above function!!! what?
    }
    //std::cout << "\nEnd Projectile Contact";
    return 0;
}
int Projectile::endContact(PhysicsBase* other)
{
    if(other->getType() == ClassType::HULL)
        enable();

    return 0;
}
void Projectile::enable()//no longer interacts with hull sensors, set to default collision state for a projectile
{
    for (b2Fixture* fix = m_pBody->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Filter filter = fix->GetFilterData();
        filter.maskBits = static_cast<uint16>(Mask::ProjectileNorm);
        fix->SetFilterData(filter);
    }
}
void Projectile::disable()//disable all collision except with hull sensors
{
    for (b2Fixture* fix = m_pBody->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Filter filter = fix->GetFilterData();
        filter.maskBits = static_cast<uint16>(Mask::ProjectileOff);
        fix->SetFilterData(filter);
    }
}
