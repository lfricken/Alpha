#ifndef WEAPONBARREL_H
#define WEAPONBARREL_H

#include "Decoration.hpp"
#include "Convert.hpp"

class Weapon;
struct WeaponBarrelData;

class WeaponBarrel
{
public:
    WeaponBarrel(const WeaponBarrelData& rData, Weapon* pWeapon);
    virtual ~WeaponBarrel();

    void fire();
    void update(const b2Vec2& rPos, float angle);//radians
    void updateVelocity(const b2Vec2& rVel);

protected:
    virtual void f_emit(const b2Vec2& rEmitPoint, float barrelAngle, const b2Vec2& rUnitVec, const b2Vec2& rBodySpeed);
private:
    b2Vec2 m_additionalMuzzleOffset;
    b2Vec2 m_barrelPositionOffset;

    float m_barrelAngle;//radians
    float m_recoilRecoverTime;
    float m_recoilDistance;//world coordinates
    float m_currentRecoilDistance;//stores our current recoil amount
    Timer m_recoilTimer;

    Weapon* m_pParent;
    std::tr1::shared_ptr<Decoration> m_spBarrelDecor;
};



struct WeaponBarrelData
{
    WeaponBarrelData() :
        muzzlePixelOffset(0,0),
        barrelPixelOffset(32,0),//standard coords
        barrelAngle(0),//degrees

        recoilDistancePixels(32),
        recoilRecoverTime(0.3)
    {
        decorData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        decorData.gfxCompData.texName = "textures/weapons/barrel.png";
        decorData.gfxCompData.animationFileName = "textures/weapons/barrel.acfg";
        decorData.gfxCompData.rotation = -90;
    }

    sf::Vector2i muzzlePixelOffset;
    sf::Vector2i barrelPixelOffset;
    float barrelAngle;//degrees

    int recoilDistancePixels;//in pixels
    float recoilRecoverTime;

    DecorationData decorData;

    virtual WeaponBarrel* generate(Weapon* pWep)
    {
        return new WeaponBarrel(*this, pWep);
    }
};


#endif // WEAPONBARREL_H
