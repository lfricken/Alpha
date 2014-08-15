#ifndef TURRET_H
#define TURRET_H

#include "GModule.hpp"
#include "Link.hpp"
#include "Weapon.hpp"

struct TurretData;
class Turret : public GModule
{
public:
    Turret();///TURRET SHOULD BE RENAMED TO HARD POINT, BECAUSE THAT IS WHERE A WEAPON IS MOUNTED
    Turret(const TurretData& rData);
    virtual ~Turret();

    void primary(const b2Vec2& coords);//we tried to fire
    void secondary(const b2Vec2& coords);//we tried to fire
    void aim(const b2Vec2& coords);//we tried aiming the turret at a place

    void destructHook();
    bool physUpdate();

    Link<Turret, Weapon>& getLinker();
protected:
private:
    void f_initialize(const TurretData& rData);

    bool m_firesPrimary;
    bool m_firesSecondary;

    Link<Turret, Weapon> m_linker;
};

struct TurretData : public GModuleData
{
    TurretData() :
        GModuleData(),
        firesPrimary(true),
        firesSecondary(false)
    {
        type = ClassType::TURRET;
        texName = "textures/turret/turret.png";
        animationFileName = "textures/turret/turret.acfg";
    }

    bool firesPrimary;
    bool firesSecondary;


    WeaponData weaponData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        TurretData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Turret(mutableCopy);
    }
};

#endif // TURRET_H
