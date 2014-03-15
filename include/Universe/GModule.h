#ifndef DGMODULE_H
#define DGMODULE_H

#include "PhysicsBase.h"
#include "GraphicsBase.h"
#include "IOBase.h"

struct GModuleData
{
    IOBaseData baseData;
    PhysicsBaseData physicsData;
    GraphicsBaseData graphicsData;
};

class GModule : public PhysicsBase, public GraphicsBase
{
public:
    GModule(const GModuleData& data);
    virtual ~GModule();

    virtual int damage(unsigned int);
protected:

private:
};

#endif // DGMODULE_H
