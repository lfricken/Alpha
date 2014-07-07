#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "Module.h"

struct ForceFieldData : public ModuleData
{
    ForceFieldData() :
        ModuleData(),
        forceStrength(400)
    {
        type = ClassType::FORCE;
        isSensor = true;
        butes.setBute(isSolid, false);
        butes.setBute(isDestructable, false);
    }

    float forceStrength;
};

class ForceField : public Module
{
public:
    ForceField();
    ForceField(const ForceFieldData& data);
    virtual ~ForceField();

    virtual int startContact(PhysicsBase* pOther);
    virtual int endContact(PhysicsBase* pOther);

    virtual bool physUpdate();
protected:
private:
    virtual void f_initialize(const ForceFieldData& data);

    b2Vec2 f_direction_absolute(const b2Vec2& direction) const;
    b2Vec2 f_direction_centroid(const b2Vec2& direction) const;//direction is either away from or towards(negative) centroid of b2Body


    float f_magnitude_constant(float magnitude) const;
    float f_magnitude_linear(float magnitude) const;
    float f_magnitude_quadratic(float magnitude) const;

    float m_strength;

    std::vector<PhysicsBase*> m_guests;
};

#endif // FORCEFIELD_H
