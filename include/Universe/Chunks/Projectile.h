#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Chunk.h"

enum ProjectileType
{
    Sphr_Sml = 0,
    Sphr_Med = 1,
    Sphr_Lrg = 2,

    Rect_Sml = 3,
    Rect_Med = 4,
    Rect_Lrg = 5,
};

struct ProjectileData : public ChunkData
{
    ProjectileData() :
        ChunkData(),
        projType(ProjectileType::Sphr_Sml)
    {
        type = ClassType::PROJECTILE;
        isBullet = true;
        awake = false;
    }

    ProjectileType projType;
};

class Projectile : public Chunk
{
public:
    Projectile();
    Projectile(const ProjectileData& sData);
    virtual ~Projectile();

    ProjectileType getProjType() const;

protected:
private:
    virtual void f_initialize(const ProjectileData& data);

    ProjectileType m_projType;
};

#endif // PROJECTILE_H
