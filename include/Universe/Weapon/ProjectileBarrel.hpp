#ifndef PROJECTILEBARREL_H
#define PROJECTILEBARREL_H

#include "WeaponBarrel.hpp"


struct ProjectileBarrelData;

class ProjectileBarrel : public WeaponBarrel
{
public:
    ProjectileBarrel(const ProjectileBarrelData& rData, Weapon* pWeapon);
    virtual ~ProjectileBarrel();

    void fire();
    void update(const b2Vec2& rPos, float angle);//radians

protected:
    void f_emit(const b2Vec2& rEmitPoint, float barrelAngle, const b2Vec2& rUnitVec, const b2Vec2& rBodySpeed);
private:

    float m_projectileVelocity;
    float m_projectileAngularVelocity;
    float m_projectileAngle;//radians

    float m_projectileDuration;
    int m_projectileType;
};



struct ProjectileBarrelData : public WeaponBarrelData
{
    ProjectileBarrelData() :
        WeaponBarrelData(),
        projectileVelocity(30),
        projectileAngularVelocity(0),
        projectileAngle(0),//degrees

        projectileDuration(5.0f),
        projectileType(0)
    {
    }

    float projectileVelocity;
    float projectileAngularVelocity;
    float projectileAngle;//DEGREES


    float projectileDuration;
    int projectileType;

    virtual WeaponBarrel* generate(Weapon* pWep)
    {
        return new ProjectileBarrel(*this, pWep);
    }
};

#endif // PROJECTILEBARREL_H
