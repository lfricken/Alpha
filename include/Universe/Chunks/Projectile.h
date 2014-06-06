#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Chunk.h"

typedef unsigned int ProjectileType;
/**
    Sphr_Sml = 0,
    Sphr_Med = 1,
    Sphr_Lrg = 2,

    Rect_Sml = 3,
    Rect_Med = 4,
    Rect_Lrg = 5,
**/

struct ProjectileData : public ChunkData
{
    ProjectileData() :
        ChunkData(),
        projType(0)
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
    void endLife();//send us to projectile Alloc

    unsigned int getListPos() const;
    void setListPos(unsigned int pos);
    void swapListPos(Projectile& other);

    float getLifeTimeRemain() const;
    void setLifeTimeRemain(float time);
    float changeLifeTimeRemain(float change);

    virtual int startContact(PhysicsBase* other);
    virtual int endContact(PhysicsBase* other);
    virtual void enable();
    virtual void disable();

protected:
private:
    virtual void f_initialize(const ProjectileData& data);

    ProjectileType m_projType;

    /**specific to interaction with ProjectileAllocator**/
    unsigned int m_listPosition;//position of us in list in ProjectileAllocator

    float m_lifeTimeRemaining;//the remaining lifetime
};

#endif // PROJECTILE_H
