#ifndef THRUSTER_H
#define THRUSTER_H

#include "GModule.h"

struct ThrusterData;
class Thruster : public GModule
{
public:
    Thruster();
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

private:
    void f_initialize(const ThrusterData& data);

};

struct ThrusterData : public GModuleData
{
    ThrusterData() :
        GModuleData(),
        force(100),
        torque(50)
    {
        type = ClassType::THRUSTER;
        texName = "textures/thruster/thruster.png";
    }
    float force;
    float torque;


    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new Thruster(*this);
    }
};

#endif // THRUSTER_H
