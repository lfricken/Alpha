#ifndef UBASE_H
#define UBASE_H

#include <stdafx.h>

#include <MultipleInheritance/IOBase.h>
#include <MultipleInheritance/GraphicsBase.h>
#include <MultipleInheritance/PhysicsBase.h>

class UBase : public IOBase, public GraphicsBase, public PhysicsBase//base physics object for all objects in the universe
{
    public:
        UBase(IOManager& rIOManager, sf::RenderWindow& rWindow, b2World& rPhysWorld);//when created, we need to make a body for this.
        virtual ~UBase();

        virtual float getHealth();
        virtual bool damage(float damage);//damage this entity, returns true if the entity has >0 health (false if it dies)

    protected:
        float m_health;//obvious

    private:
};

#endif // UBASE_H
