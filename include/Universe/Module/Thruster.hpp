#ifndef THRUSTER_H
#define THRUSTER_H

#include "GModule.hpp"
#include "Spinner.hpp"

struct ThrusterData;
class Thruster : public GModule
{
public:
    Thruster(const ThrusterData& rData);
    virtual ~Thruster();

    virtual bool physUpdate();
    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    virtual void rollLeft();
    virtual void rollRight();

    void thrust(const b2Vec2& direction);//apply a force in that direction = m_force
    void torque(bool isCCW);//if true, rotate counter clockwise

protected:
    float m_force;
    float m_torque;
    float m_energyConsumption;

private:

    Spinner m_turbine;
    ///Decoration m_nozzle;
};

struct ThrusterData : public GModuleData
{
    ThrusterData() :
        GModuleData(),
        force(100),
        torque(50),
        energyConsumption(6),//units per second
        turbineData()
    {
        type = ClassType::THRUSTER;
        texName = "textures/thruster/thruster.png";
        animationFileName = "textures/thruster/thruster.acfg";

        turbineData.spinRate = 120;
        turbineData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesLower;
        turbineData.gfxCompData.animationFileName = "textures/thruster/fan.acfg";
        turbineData.gfxCompData.texName = "textures/thruster/fan.png";
    }

    float force;
    float torque;
    float energyConsumption;

    SpinnerData turbineData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        ThrusterData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Thruster(mutableCopy);
    }
};

#endif // THRUSTER_H
