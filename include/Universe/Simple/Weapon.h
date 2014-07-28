#ifndef WEAPON_H
#define WEAPON_H

#include "AmmoContainer.h"
#include "WeaponBarrel.h"
#include "Link.h"

struct FireCommand
{
    float delay;
    unsigned int barrelIndex;
};

struct WeaponData
{
    WeaponData() :
        refireDelay(1),
        canPivot(true)
    {
        decorationData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        decorationData.gfxCompData.texName = "textures/barrels/chain_turret.png";
        decorationData.gfxCompData.texTileSize = sf::Vector2f(32,64);
        decorationData.gfxCompData.rotation = leon::degToRad(-90);
    }

    AmmoContainer ammo;//ammo data
    float refireDelay;//time till we can shoot again

    bool canPivot;
    DecorationData decorationData;

    std::vector<FireCommand> fireCommandList;//instructions for firing
    std::vector<WeaponBarrelData> barrelData;
};


class Turret;
class Weapon
{
public:
    Weapon(const WeaponData& rData);
    virtual ~Weapon();


    void primary(const b2Vec2& coords);//we tried to fire
    void secondary(const b2Vec2& coords);//we tried to fire
    void aim(const b2Vec2& coords);//we tried aiming the turret at a place
    float getAimAngle() const;//radians

    bool checkFireState();

    Link<Weapon, Turret>& getLinker();
protected:
private:
    Link<Weapon, Turret> m_linker;

    void f_queueCommands();//the gun will queue firing commands

    AmmoContainer m_ammoContainer;//manages magazine size, count, reload time, and total ammo
    Timer m_refireTimer;

    float m_aimAngle;//radians
    bool m_canPivot;
    std::tr1::shared_ptr<Decoration> m_spGunMantle;

    Timer m_commandTimer;
    std::vector<FireCommand> m_fireCommands;
    std::vector<FireCommand> m_queuedCommands;
    std::vector<WeaponBarrel> m_barrels;
};

#endif // WEAPON_H
