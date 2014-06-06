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
    m_projType = data.projType;
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
int Projectile::startContact(PhysicsBase* other)
{
    /**do stuff**/
    if(other->getButes().getBute(Butes::isSolid))
    {
        ///call the function to deliver some sort of package
        endLife();///put this in the above function!!!
    }

    return 0;
}
int Projectile::endContact(PhysicsBase* other)
{
    cout << "\nEnd Contact Called.";
}
void Projectile::enable()//no longer interacts with hull sensors, set to default collision state for a projectile
{

}
void Projectile::disable()//disable all collision except with hull sensors
{

}
