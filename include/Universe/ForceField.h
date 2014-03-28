#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "Module.h"

struct ForceFieldData : public ModuleData
{
    ForceFieldData() :
        ModuleData()
        {}
};

class ForceField : public Module
{
public:
    ForceField();
    ForceField(const ForceFieldData& data);
    virtual ~ForceField();

    virtual int startContact(void* other);
    virtual int preSolveContact(void* other);
    virtual int postSolveContact(void* other);

    virtual bool physUpdate();
protected:
private:
    virtual void f_initialize(const ForceFieldData& data);

    PhysicsBase* m_target;//for convienience;
    b2Body* m_targetBody;
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
