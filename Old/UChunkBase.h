#ifndef UCHUNKBASE_H
#define UCHUNKBASE_H

#include <stdafx.h>
#include <MultipleInheritance/PhysicsBase.h>

class UChunkBase
{
public:
    UChunkBase(b2World& rPhysWorld, b2Vec2 coordinate);
    virtual ~UChunkBase();

protected:
    b2Body* m_pBody;
    b2World& m_rPhysWorld;
private:
};

#endif // UCHUNKBASE_H
