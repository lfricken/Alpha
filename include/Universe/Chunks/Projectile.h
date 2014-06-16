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
        damage(0, 0),
        projType(0)

    {
        type = ClassType::PROJECTILE;
        bodyType = b2BodyType::b2_dynamicBody;
        isBullet = true;
        awake = false;
    }
    T_Damage damage;
    ProjectileType projType;

};

class Projectile : public Chunk
{
public:
    Projectile();
    Projectile(const ProjectileData& sData);
    virtual ~Projectile();

    void setDamage(T_Damage damage);//set the damage this projectile will deal

    ProjectileType getProjType() const;
    void endLife();//send us to projectile Alloc

    unsigned int getListPos() const;
    void setListPos(unsigned int pos);
    void swapListPos(Projectile& other);

    float getLifeTimeRemain() const;
    void setLifeTimeRemain(float time);
    float changeLifeTimeRemain(float change);

    virtual void wake(const b2Vec2& pos, float angle, const b2Vec2& velocity, float angVel);
    virtual int startContact(PhysicsBase* other);
    virtual int endContact(PhysicsBase* other);
    virtual void enable();//no longer interacts with hull sensors, set to default collision state for a projectile
    virtual void disable();//disable all collision except with hull sensors

protected:
private:
    virtual void f_initialize(const ProjectileData& data);

    Package m_damagePackage;


    ProjectileType m_projType;

    /**specific to interaction with ProjectileAllocator**/
    unsigned int m_listPosition;//position of us in list in ProjectileAllocator

    float m_lifeTimeRemaining;//the remaining lifetime
};

#endif // PROJECTILE_H
