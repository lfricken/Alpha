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
        {}
};

class GModule : public PhysicsBase, public GraphicsBase
{
public:
    GModule();
    GModule(const GModuleData& data);
    virtual ~GModule();

    virtual int damage(int);

protected:
    virtual void f_initialize(const GModuleData& data);

private:
};

#endif // DGMODULE_H
