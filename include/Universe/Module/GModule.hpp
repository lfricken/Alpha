#ifndef DGMODULE_H
#define DGMODULE_H

#include "PhysicsBase.hpp"
#include "GraphicsBase.hpp"
#include "IOBase.hpp"
#include "Chunk.hpp"

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

    void destruct();//if our health drops too low, try and "destruct"
    virtual void destructHook();//hooks into end of destruct
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


    T_Armor armor;
    T_Health health;
    T_Health healthMax;


    virtual GModule* generate(Chunk* pChunk) const
    {
        GModuleData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
                mutableCopy.pChunk = pChunk;
        return new GModule(mutableCopy);
    }
};

#endif // DGMODULE_H
