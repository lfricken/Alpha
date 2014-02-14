#ifndef UDYNAMICCHUNK_H
#define UDYNAMICCHUNK_H

#include <stdafx.h>
#include <Universe/DGModule.h>
#include <Universe/DModule.h>

class UDynamicChunk
{
public:
    UDynamicChunk(b2World& rPhysWorld, b2Vec2 coordinate);
    ~UDynamicChunk();

    virtual void add(DGModule& tempCopy);
    virtual void add(DModule& tempCopy);
    ///virtual void remove();//how to remove a module

    virtual void draw();

protected:
    b2Body* m_pBody;
    b2World& m_rPhysWorld;

    std::vector<DGModule> m_DGModuleList;
    std::vector<DModule> m_DModuleList;

private:
};

#endif // UDYNAMICCHUNK_H
