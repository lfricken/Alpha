#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Chunk.h"

struct ProjectileData : public ChunkData
{
    ProjectileData() :
        ChunkData()
        {}
};

class Projectile : public Chunk
{
    public:
        Projectile();
        Projectile(const ProjectileData& sData);
        virtual ~Projectile();


    protected:
    private:
        virtual void f_initialize(const ProjectileData& data);
};

#endif // PROJECTILE_H
