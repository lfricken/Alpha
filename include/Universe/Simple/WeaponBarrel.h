#ifndef WEAPONBARREL_H
#define WEAPONBARREL_H

#include "Decoration.h"
#include "Angles.h"

class Weapon;

struct WeaponBarrelData
{
    WeaponBarrelData() :
        projectileVelocity(30),
        projectileAngularVelocity(0),
        projectileAngle(0),
        muzzlePixelOffset(0,0),
        projectileConsumption(1),
        projectileDuration(5.0f),
        projectileType(0),
        barrelPixelOffset(32,0),//standard coords
        barrelAngle(0),
        recoilDistancePixels(32),
        recoilRecoverTime(0.3)
    {
        decorData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesLower;
        decorData.gfxCompData.texName = "textures/barrels/chain_barrels.png";
        decorData.gfxCompData.texTileSize = sf::Vector2f(16,64);
        decorData.gfxCompData.rotation = leon::degToRad(-90);
    }

    float projectileVelocity;
    float projectileAngularVelocity;
    float projectileAngle;
    sf::Vector2i muzzlePixelOffset;

    int projectileConsumption;
    float projectileDuration;

    int projectileType;
    sf::Vector2i barrelPixelOffset;
    float barrelAngle;//radians

    int recoilDistancePixels;//in pixels
    float recoilRecoverTime;

    DecorationData decorData;
};

class WeaponBarrel
{
public:
    WeaponBarrel(const WeaponBarrelData& rData, Weapon* pWeapon);
    virtual ~WeaponBarrel();

    void fire();
    void update(const b2Vec2& rPos, float angle);//radians

protected:
private:
    float m_projectileVelocity;
    float m_projectileAngularVelocity;
    float m_projectileAngle;
    b2Vec2 m_additionalMuzzleOffset;
    float m_projectileDuration;
    int m_projectileType;

    int m_projectileConsumption;

    b2Vec2 m_barrelPositionOffset;
    float m_barrelAngle;//radians

    float m_recoilRecoverTime;
    float m_recoilDistance;//world coordinates
    float m_currentRecoilDistance;//stores our current recoil amount
    Timer m_recoilTimer;


    Weapon* m_pParent;
    std::tr1::shared_ptr<Decoration> m_spBarrelDecor;
};

#endif // WEAPONBARREL_H
