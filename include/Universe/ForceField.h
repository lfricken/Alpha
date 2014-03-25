#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "Module.h"

struct ForceFieldData
{
    ForceFieldData(){moduleBaseData.physicsData.isSensor = true;}
    ModuleData moduleBaseData;
};

class ForceField : public Module
{
public:
    ForceField(ForceFieldData& data);
    virtual ~ForceField();

    virtual bool physUpdate();
protected:
private:
    PhysicsBase* m_target;//for convienience;
    b2Fixture* m_targetFixture;
    b2ContactEdge* m_contactList;

    float m_strength;
    bool m_hasContact;

    b2Vec2 m_force;
    b2Vec2 m_ourCoords;
    b2Vec2 m_theirCoords;
    float m_distance;
    float m_theirMass;
    b2Vec2 m_direction;
};

#endif // FORCEFIELD_H
