#ifndef UDYNAMICCHUNK_H
#define UDYNAMICCHUNK_H

#include <stdafx.h>
#include <Universe/GModule.h>
#include <Universe/Module.h>

class UDynamicChunk
{
public:
    UDynamicChunk(b2World& rPhysWorld, b2Vec2 coordinate);
    ~UDynamicChunk();

    virtual void add(GModule& tempCopy);
    virtual void add(Module& tempCopy);
    ///virtual void remove();//how to remove a module

    virtual void draw();

protected:
    b2Body* m_pBody;
    b2World& m_rPhysWorld;

    std::vector<GModule> m_GModuleList;
    std::vector<Module> m_DModuleList;

private:
};

#endif // UDYNAMICCHUNK_H
