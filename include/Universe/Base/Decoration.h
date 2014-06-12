#ifndef DECORATION_H
#define DECORATION_H

#include "IOBase.h"
#include "GraphicsComponent.h"

struct DecorationData : public IOBaseData
{
    DecorationData() :
        IOBaseData(),
        gfxCompData()
    {
        type = ClassType::DECORATION;
    }

    GraphicsComponentData gfxCompData;
};

class Decoration : public IOBase
{
public:
    Decoration();
    Decoration(const DecorationData& rData);
    virtual ~Decoration();

protected:
private:
    virtual void f_init(const DecorationData& rData);

    GraphicsComponent m_gfxComp;
};

#endif // DECORATION_H
