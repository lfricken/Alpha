#ifndef TURRET_H
#define TURRET_H

#include "GModule.h"
#include "AmmoContainer.h"
#include "Decoration.h"
#include "TurretBarrel.h"

struct FireCommand
{
    float delay;
    unsigned int barrelIndex;
};



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
    float getAimAngle() const;//radians

    void queueCommands();//the gun will queue firing commands

    bool physUpdate();
protected:
private:
    void f_initialize(const TurretData& rData);

    AmmoContainer m_ammoContainer;//manages magazine size, count, reload time, and total ammo
    Timer m_refireTimer;

    float m_aimAngle;//radians
    bool m_canPivot;
    std::tr1::shared_ptr<Decoration> m_spTurretTop;

    Timer m_commandTimer;
    std::vector<FireCommand> m_fireCommands;
    std::vector<FireCommand> m_queuedCommands;
    std::vector<TurretBarrel> m_barrels;
};

struct TurretData : public GModuleData
{
    TurretData() :
        GModuleData(),
        refireDelay(1),
        canPivot(true)
    {
        type = ClassType::TURRET;
        texName = "textures/armor/armor.png";

        decorationData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        decorationData.gfxCompData.texName = "textures/barrels/chain_turret.png";
        decorationData.gfxCompData.texTileSize = sf::Vector2f(32,64);
        decorationData.gfxCompData.rotation = 90;
    }

    AmmoContainer ammo;//ammo data
    float refireDelay;//time till we can shoot again

    bool canPivot;
    DecorationData decorationData;

    std::vector<FireCommand> fireCommandList;//instructions for firing
    std::vector<TurretBarrelData> barrelData;

    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new Turret(*this);
    }
};

#endif // TURRET_H
