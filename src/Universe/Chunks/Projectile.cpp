#include "Projectile.h"

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
    //nothing new to do atm
}
ProjectileType Projectile::getProjType() const
{
    return m_projType;
}
