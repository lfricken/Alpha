#ifndef THRUSTER_H
#define THRUSTER_H

#include "GModule.hpp"
#include "Spinner.hpp"
#include "Needle.hpp"

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
    float m_torqueAngle;//angle that thruster will go to when turning
    float m_energyConsumption; // J/s

private:

    Spinner m_turbine;
    Needle m_nozzle;
};

struct ThrusterData : public GModuleData
{
    ThrusterData() :
        GModuleData(),
        force(100),
        torque(100),
        torqueAngle(60),
        energyConsumption(6),//units per second
        turbineData(),
        nozzleData()
    {
        type = ClassType::THRUSTER;
        texName = "textures/thruster/thruster.png";
        animationFileName = "textures/thruster/thruster.acfg";

        turbineData.gfxCompData.gfxLayer = GraphicsLayer::ShipUnder;
        turbineData.gfxCompData.animationFileName = "textures/thruster/fan.acfg";
        turbineData.gfxCompData.texName = "textures/thruster/fan.png";
        turbineData.gfxCompData.dimensions = sf::Vector2f(128, 128);

        nozzleData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        nozzleData.gfxCompData.animationFileName = "textures/thruster/nozzle.acfg";
        nozzleData.gfxCompData.texName = "textures/thruster/nozzle.png";
        nozzleData.gfxCompData.dimensions = sf::Vector2f(128, 896);
    }

    float force;
    float torque;
    float torqueAngle;
    float energyConsumption;

    SpinnerData turbineData;
    NeedleData nozzleData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        ThrusterData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Thruster(mutableCopy);
    }
};

#endif // THRUSTER_H
