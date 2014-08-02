#ifndef TURRET_H
#define TURRET_H

#include "GModule.hpp"
#include "Link.hpp"
#include "Weapon.hpp"

struct TurretData;
class Turret : public GModule
{
public:
    Turret();
    Turret(const TurretData& rData);
    virtual ~Turret();

    void primary(const b2Vec2& coords);//we tried to fire
    void secondary(const b2Vec2& coords);//we tried to fire
    void aim(const b2Vec2& coords);//we tried aiming the turret at a place

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
    }

    bool firesPrimary;
    bool firesSecondary;


    WeaponData weaponData;

    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new Turret(*this);
    }
};

#endif // TURRET_H
