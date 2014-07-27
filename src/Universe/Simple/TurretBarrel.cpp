#include "TurretBarrel.h"
#include "Turret.h"
#include "globals.h"
#include "Angles.h"

TurretBarrel::TurretBarrel(const TurretBarrelData& rData)
{
    m_projectileVelocity = rData.projectileVelocity;
    m_projectileAngularVelocity = rData.projectileAngularVelocity;
    float m_projectileAngle = rData.projectileAngle;
    m_additionalMuzzleOffset;

    m_projectileConsumption = rData.projectileConsumption;
    m_projectileDuration = rData.projectileDuration;

    m_projectileType = rData.projectileType;
    m_barrelOffset = rData.barrelOffset;

    m_pParent = rData.pParent;
    m_spBarrelDecor.reset(new Decoration(rData.decorData));
}
TurretBarrel::~TurretBarrel()
{

}
void TurretBarrel::fire()
{
    ///check for ammo first

    b2Vec2 velVec;

    velVec.x = m_projectileVelocity*cos(m_pParent->getAimAngle());
    velVec.y = m_projectileVelocity*sin(m_pParent->getAimAngle());

    Projectile* pBullet = game.getGameUniverse().getProjAlloc().getProjectile(0);
    pBullet->setLifeTimeRemain(m_projectileDuration);
    pBullet->wake(m_pParent->getCenter(), atan(velVec.y/velVec.x), velVec+m_pParent->getBody()->GetLinearVelocity(), m_projectileAngularVelocity);
    ///we need to compute where it comes from, not just the center of fixture
}
void TurretBarrel::update(const b2Vec2& rPos, float angle)//radians
{
    m_spBarrelDecor->setRotation(leon::radToDeg(angle));
    ///DO THE MORE ADVANCED CALCULATION for position
    m_spBarrelDecor->setPosition(rPos);
}
