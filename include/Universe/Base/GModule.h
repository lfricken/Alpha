#ifndef DGMODULE_H
#define DGMODULE_H

#include "PhysicsBase.h"
#include "GraphicsBase.h"
#include "IOBase.h"
#include "Chunk.h"

struct GModuleData;
class GModule : public PhysicsBase, public GraphicsBase
{
public:
    GModule();
    GModule(const GModuleData& data);
    virtual ~GModule();

    IOBaseReturn input(IOBaseArgs);//damage function implemented

    virtual void primary(const b2Vec2& coords);
    virtual void secondary(const b2Vec2& coords);
    virtual void aim(const b2Vec2& coords);
    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    virtual void rollLeft();
    virtual void rollRight();
    virtual void special_1();
    virtual void special_2();
    virtual void special_3();
    virtual void special_4();

    T_Health damage(T_Damage damage);
    T_Health heal(T_Health h);
    T_Health getHealth() const;
    virtual void destruct();//if our health drops too low, try and "destruct"
    bool isDestroyed() const;
protected:
    virtual void f_initialize(const GModuleData& data);

private:
    HealthData m_health;
    bool m_isDestroyed;
};

struct GModuleData : public PhysicsBaseData, public GraphicsBaseData
{
    GModuleData() :
        PhysicsBaseData(),
        GraphicsBaseData(),
        armor(0),
        health(1000),
        healthMax(1000)
    {
        type = ClassType::GMODULE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        butes.setBute(isSolid, true);
        butes.setBute(isDestructable, true);
    }
    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new GModule(*this);
    }

    T_Armor armor;
    T_Health health;
    T_Health healthMax;
};

#endif // DGMODULE_H
