#ifndef DGMODULE_H
#define DGMODULE_H

#include "PhysicsBase.h"
#include "GraphicsBase.h"
#include "IOBase.h"

struct GModuleData : public PhysicsBaseData, public GraphicsBaseData
{
    GModuleData() :
        PhysicsBaseData(),
        GraphicsBaseData()
    {
        type = ClassType::GMODULE;
        butes.setBute(isSolid, true);
        butes.setBute(isDestructable, true);
    }
};

class GModule : public PhysicsBase, public GraphicsBase
{
public:
    GModule();
    GModule(const GModuleData& data);
    virtual ~GModule();

    IOBaseReturn input_1(IOBaseArgs) final;//damage function implemented
    T_Health damage(T_Damage damage);
    T_Health heal(T_Health health);
    T_Health getHealth() const;

    void destruct();//if our health drops too low, try and "destruct"

protected:
    virtual void f_initialize(const GModuleData& data);

private:
    HealthData m_health;
    bool m_isDestroyed;
};

#endif // DGMODULE_H
