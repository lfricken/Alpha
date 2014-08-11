#ifndef DMODULE_H
#define DMODULE_H

#include "IOBase.hpp"
#include "PhysicsBase.hpp"
#include "Chunk.hpp"

struct ModuleData;
class Module : public PhysicsBase
{
public:
    Module();
    Module(const ModuleData& data);
    virtual ~Module();

protected:
private:
    virtual void f_initialize(const ModuleData& data);
};

struct ModuleData : public PhysicsBaseData
{
    ModuleData() :
        PhysicsBaseData()
    {
        type = ClassType::MODULE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        butes.setBute(isSolid, true);
        butes.setBute(isDestructable, false);
    }
    virtual Module* generate(Chunk* pChunk) const
    {
        ModuleData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Module(mutableCopy);
    }
};

#endif // DMODULE_H
