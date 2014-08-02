#ifndef WEAPON_H
#define WEAPON_H

#include "AmmoContainer.hpp"
#include "WeaponBarrel.hpp"
#include "Link.hpp"
#include "Magazine.hpp"

struct FireCommand
{
    FireCommand() :
        delay(0),
        barrelIndex(0)
        {
        }

    float delay;
    unsigned int barrelIndex;
};

struct WeaponData
{
    WeaponData() :
        energyConsumption(1),
        ammoConsumption(1),
        ammoType(AmmoType::Gauss),
        magazine(5),

        refireDelay(1),
        canPivot(true),
        startAngle(90)//degrees
    {
        decorationData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        decorationData.gfxCompData.texName = "textures/barrels/chain_turret.png";
        decorationData.gfxCompData.texTileSize = sf::Vector2f(32,64);
        decorationData.gfxCompData.rotation = -90;//this is negative because our gun sprites start facing up, so we need to rotate them 90degs CW
    }
    T_Energy energyConsumption;
    T_Ammo ammoConsumption;
    AmmoType ammoType;
    Magazine magazine;

    float refireDelay;//time till we can shoot again

    bool canPivot;
    float startAngle;//degrees
    DecorationData decorationData;

    std::vector<FireCommand> primeCommandList;//instructions for firing
    std::vector<FireCommand> secondaryCommandList;
    std::vector<std::tr1::shared_ptr<WeaponBarrelData> > barrelData;
};


class Turret;
class Weapon
{
public:
    Weapon(const WeaponData& rData);
    virtual ~Weapon();


    void primary(const b2Vec2& targetCoords);//we tried to fire
    void secondary(const b2Vec2& targetCoords);//we tried to fire
    void aim(const b2Vec2& rOurPos, const b2Vec2& targetPos);//we tried aiming the turret at a place
    float getAimAngle() const;//radians

    bool checkFireState(const b2Vec2& rOurPos);

    Link<Weapon, Turret>& getLinker();
protected:
private:
    mutable Link<Weapon, Turret> m_linker;

    void f_queuePrimaryCommands();//the gun will queue firing commands
    void f_queueSecondaryCommands();//the gun will queue firing commands

    T_Energy m_energyConsumption;
    T_Ammo m_ammoConsumption;
    AmmoType m_ammoType;
    Magazine m_magazine;///SHOULD BE A MAGAZINE, NOT A FLOAT

    Timer m_refireTimer;

    float m_aimAngle;//radians
    float m_startAngle;//radians
    bool m_canPivot;
    std::tr1::shared_ptr<Decoration> m_spGunMantle;

    Timer m_commandTimer;
    std::vector<FireCommand> m_primaryFireCommands;
    std::vector<FireCommand> m_secondaryFireCommands;

    std::vector<FireCommand> m_queuedCommands;
    std::vector<std::tr1::shared_ptr<WeaponBarrel> > m_barrels;
};

#endif // WEAPON_H
