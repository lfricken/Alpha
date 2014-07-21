#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "Trigger.h"


struct ForceFieldData;
class ForceField : public Trigger
{
public:
    ForceField();
    ForceField(const ForceFieldData& data);
    virtual ~ForceField();


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
};

struct ForceFieldData : public TriggerData
{
    ForceFieldData() :
        TriggerData(),
        forceStrength(400)
    {
        density = 0;
        shape = Shape::CIRCLE;
        categoryBits = Category::ShipForceField;
        maskBits = Mask::ShipForceField;
        type = ClassType::TRIGGER;
    }
    virtual Module* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new ForceField(*this);
    }

    float forceStrength;
};

#endif // FORCEFIELD_H
