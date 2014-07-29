#include "WeaponBarrel.h"
#include "Turret.h"
#include "globals.h"
#include "Angles.h"
#include "Projectile.h"
#include "Decoration.h"

WeaponBarrel::WeaponBarrel(const WeaponBarrelData& rData, Weapon* pWeapon)
{
    m_pParent = pWeapon;
    m_projectileVelocity = rData.projectileVelocity;
    m_projectileAngularVelocity = rData.projectileAngularVelocity;
    float m_projectileAngle = rData.projectileAngle;

    m_additionalMuzzleOffset.x = rData.muzzlePixelOffset.x/static_cast<float>(scale);
    m_additionalMuzzleOffset.y = rData.muzzlePixelOffset.y/static_cast<float>(scale);

    m_projectileConsumption = rData.projectileConsumption;
    m_projectileDuration = rData.projectileDuration;

    m_projectileType = rData.projectileType;
    m_barrelPositionOffset.x = rData.barrelPixelOffset.x/static_cast<float>(scale);
    m_barrelPositionOffset.y = rData.barrelPixelOffset.y/static_cast<float>(scale);
    m_barrelAngle = rData.barrelAngle;

    m_recoilDistance = rData.recoilDistancePixels/static_cast<float>(scale);
    m_recoilRecoverTime = rData.recoilRecoverTime;
    m_currentRecoilDistance = 0;
    m_recoilTimer.getTimeElapsed();

    m_spBarrelDecor.reset(new Decoration(rData.decorData));
}
WeaponBarrel::~WeaponBarrel()
{

}
void WeaponBarrel::fire()
{
   // m_pParent->getLinker().getTargetPtr()->getChunk().getAmmoPool().consume
    ///check for ammo first

    b2Vec2 velVec;
    float angle = m_pParent->getAimAngle() + m_barrelAngle;


    velVec.x = m_projectileVelocity*cos(angle);
    velVec.y = m_projectileVelocity*sin(angle);

    b2Vec2 tempBarrelOffset;
    tempBarrelOffset.x = cos(-angle)*(m_barrelPositionOffset.x+m_additionalMuzzleOffset.x) + sin(-angle)*(m_barrelPositionOffset.y+m_additionalMuzzleOffset.y);
    tempBarrelOffset.y = -sin(-angle)*(m_barrelPositionOffset.x+m_additionalMuzzleOffset.x) + cos(-angle)*(m_barrelPositionOffset.y+m_additionalMuzzleOffset.y);

    Projectile* pBullet = game.getGameUniverse().getProjAlloc().getProjectile(m_projectileType);
    pBullet->setLifeTimeRemain(m_projectileDuration);
    pBullet->wake(m_pParent->getLinker().getTargetPtr()->getCenter()+tempBarrelOffset, atan(velVec.y/velVec.x), velVec+m_pParent->getLinker().getTargetPtr()->getBody()->GetLinearVelocity(), m_projectileAngularVelocity);

    m_currentRecoilDistance = m_recoilDistance;
}
void WeaponBarrel::update(const b2Vec2& rPos, float angle)//radians
{
    m_spBarrelDecor->setRotation(angle+m_barrelAngle);

    b2Vec2 tempBarrelOffset;
    tempBarrelOffset.x = cos(-angle)*(m_barrelPositionOffset.x-m_currentRecoilDistance) + sin(-angle)*m_barrelPositionOffset.y;
    tempBarrelOffset.y = -sin(-angle)*(m_barrelPositionOffset.x-m_currentRecoilDistance) + cos(-angle)*m_barrelPositionOffset.y;
    m_spBarrelDecor->setPosition(rPos+tempBarrelOffset);

    float time = m_recoilTimer.getTimeElapsed();
    if(m_currentRecoilDistance > 0)
    {
        m_currentRecoilDistance -= (time/m_recoilRecoverTime)*m_recoilDistance;
    }
}
