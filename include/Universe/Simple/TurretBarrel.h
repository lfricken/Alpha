#ifndef TURRETBARREL_H
#define TURRETBARREL_H

#include "Decoration.h"
#include "Projectile.h"

class Turret;

struct TurretBarrelData
{
    TurretBarrelData() :
        projectileVelocity(30),
        projectileAngularVelocity(0),
        projectileAngle(0),
        additionalMuzzleOffset(1,0),
        projectileConsumption(1),
        projectileDuration(5.0f),
        projectileType(0),
        barrelOffset(1,0)
    {
        decorData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesLower;
        decorData.gfxCompData.texName = "textures/barrels/chain_barrels.png";
        decorData.gfxCompData.texTileSize = sf::Vector2f(32,64);
        decorData.gfxCompData.rotation = 90;
    }

    float projectileVelocity;
    float projectileAngularVelocity;
    float projectileAngle;
    b2Vec2 additionalMuzzleOffset;

    int projectileConsumption;
    float projectileDuration;

    ProjectileType projectileType;
    b2Vec2 barrelOffset;

    Turret* pParent;
    DecorationData decorData;
};

class TurretBarrel
{
public:
    TurretBarrel(const TurretBarrelData& rData);
    virtual ~TurretBarrel();

    void fire();
    void update(const b2Vec2& rPos, float angle);

protected:
private:
    float m_projectileVelocity;
    float m_projectileAngularVelocity;
    float m_projectileAngle;
    b2Vec2 m_additionalMuzzleOffset;

    int m_projectileConsumption;
    float m_projectileDuration;

    ProjectileType m_projectileType;
    b2Vec2 m_barrelOffset;

    Turret* m_pParent;
    std::tr1::shared_ptr<Decoration> m_spBarrelDecor;
};

#endif // TURRETBARREL_H
