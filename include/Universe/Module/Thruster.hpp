#ifndef THRUSTER_H
#define THRUSTER_H

#include "GModule.hpp"

struct ThrusterData;
class Thruster : public GModule
{
public:
    Thruster(const ThrusterData& data);
    virtual ~Thruster();

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
};

struct ThrusterData : public GModuleData
{
    ThrusterData() :
        GModuleData(),
        force(100),
        torque(50),
        energyConsumption(6)//units per second
    {
        type = ClassType::THRUSTER;
        texName = "textures/thruster/thruster.png";
        animationFileName = "textures/thruster/thruster.acfg";
    }
    float force;
    float torque;
    float energyConsumption;


    virtual GModule* generate(Chunk* pChunk) const
    {
        ThrusterData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Thruster(mutableCopy);
    }
};

#endif // THRUSTER_H
