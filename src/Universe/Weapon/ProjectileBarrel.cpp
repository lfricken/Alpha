#include "ProjectileBarrel.hpp"

#include "Turret.hpp"

ProjectileBarrel::ProjectileBarrel(const ProjectileBarrelData& rData, Weapon* pWeapon) : WeaponBarrel(static_cast<WeaponBarrelData>(rData), pWeapon)
{
    m_projectileVelocity = rData.projectileVelocity;
    m_projectileAngularVelocity = rData.projectileAngularVelocity;
    m_projectileAngle = leon::degToRad(rData.projectileAngle);

    m_projectileDuration = rData.projectileDuration;
    m_projectileType = rData.projectileType;
}
ProjectileBarrel::~ProjectileBarrel()
{

}
void ProjectileBarrel::f_emit(const b2Vec2& rEmitPoint, float barrelAngle, const b2Vec2& rUnitVec, const b2Vec2& rBodySpeed)
{
    b2Vec2 finalVelVec = b2Vec2((rUnitVec.x*m_projectileVelocity)+rBodySpeed.x, (rUnitVec.y*m_projectileVelocity)+rBodySpeed.y);

    Projectile* pBullet = game.getGameUniverse().getProjAlloc().getProjectile(m_projectileType);
    pBullet->setLifeTimeRemain(m_projectileDuration);
    pBullet->wake(rEmitPoint, barrelAngle+m_projectileAngle, finalVelVec, m_projectileAngularVelocity);
}
