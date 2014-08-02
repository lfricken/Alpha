#include "WeaponBarrel.hpp"

#include "Turret.hpp"
#include "globals.hpp"
#include "Convert.hpp"
#include "Projectile.hpp"
#include "Decoration.hpp"

WeaponBarrel::WeaponBarrel(const WeaponBarrelData& rData, Weapon* pWeapon)
{
    m_additionalMuzzleOffset.x = rData.muzzlePixelOffset.x/static_cast<float>(scale);
    m_additionalMuzzleOffset.y = rData.muzzlePixelOffset.y/static_cast<float>(scale);
    m_barrelPositionOffset.x = rData.barrelPixelOffset.x/static_cast<float>(scale);
    m_barrelPositionOffset.y = rData.barrelPixelOffset.y/static_cast<float>(scale);

    m_barrelAngle = leon::degToRad(rData.barrelAngle);

    m_recoilRecoverTime = rData.recoilRecoverTime;
    m_recoilDistance = rData.recoilDistancePixels/static_cast<float>(scale);
    m_currentRecoilDistance = 0;
    m_recoilTimer.getTimeElapsed();

    m_pParent = pWeapon;
    m_spBarrelDecor.reset(new Decoration(rData.decorData));
}
WeaponBarrel::~WeaponBarrel()
{

}
void WeaponBarrel::fire()
{
    b2Vec2 unitVec;
    float angle = m_pParent->getAimAngle() + m_barrelAngle;

    unitVec.x = cos(angle);
    unitVec.y = sin(angle);

    b2Vec2 emitPosition;
    emitPosition.x = cos(-angle-m_barrelAngle)*(m_barrelPositionOffset.x+m_additionalMuzzleOffset.x) + sin(-angle-m_barrelAngle)*(m_barrelPositionOffset.y+m_additionalMuzzleOffset.y);
    emitPosition.y = -sin(-angle-m_barrelAngle)*(m_barrelPositionOffset.x+m_additionalMuzzleOffset.x) + cos(-angle-m_barrelAngle)*(m_barrelPositionOffset.y+m_additionalMuzzleOffset.y);
    emitPosition += m_pParent->getLinker().getTargetPtr()->getCenter();
    f_emit(emitPosition, angle, unitVec, m_pParent->getLinker().getTargetPtr()->getBody()->GetLinearVelocity());

    m_currentRecoilDistance = m_recoilDistance;
}
void WeaponBarrel::update(const b2Vec2& rPos, float angle)//radians
{
    m_spBarrelDecor->setRotation(angle+m_barrelAngle);

    b2Vec2 tempBarrelOffset;
    tempBarrelOffset.x = cos(-angle-m_barrelAngle)*(m_barrelPositionOffset.x-m_currentRecoilDistance) + sin(-angle-m_barrelAngle)*m_barrelPositionOffset.y;
    tempBarrelOffset.y = -sin(-angle-m_barrelAngle)*(m_barrelPositionOffset.x-m_currentRecoilDistance) + cos(-angle-m_barrelAngle)*m_barrelPositionOffset.y;
    m_spBarrelDecor->setPosition(rPos+tempBarrelOffset);

    float time = m_recoilTimer.getTimeElapsed();
    if(m_currentRecoilDistance > 0)
    {
        m_currentRecoilDistance -= (time/m_recoilRecoverTime)*m_recoilDistance;
    }
}
void WeaponBarrel::f_emit(const b2Vec2& rEmitPoint, float barrelAngle, const b2Vec2& rUnitVec, const b2Vec2& rBodySpeed)
{

}
