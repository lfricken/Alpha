#ifndef DGMODULE_H
#define DGMODULE_H

#include "PhysicsBase.h"
#include "GraphicsBase.h"
#include "IOBase.h"

struct GModuleData : public Data
{
    PhysicsBaseData physicsData;
    GraphicsBaseData graphicsData;
};

class GModule : public PhysicsBase, public GraphicsBase
{
public:
    GModule(GModuleData& data);
    GModule(const GModule& old);///may be obsolete, and bad, should probably delete this
    virtual ~GModule();

    virtual bool input(Package& rPackage);

protected:


private:
};

#endif // DGMODULE_H
