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
int Projectile::startContact(void* other)
{
    /**do stuff**/
    endLife();
    return 0;
}
