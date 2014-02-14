#ifndef DCHUNK_H
#define DCHUNK_H

#include <stdafx.h>
#include <Universe/DGModule.h>
#include <Universe/DModule.h>
#include <Universe/MultiTileMap.h>

class DChunk : public IOBase
{
public:
    DChunk();
    DChunk(b2Vec2 coordinate);
    virtual ~DChunk();

    virtual void add(std::vector<DGModuleData>& data);
    ///virtual void remove();//how to remove a module
    virtual b2Body* getBody();

    virtual void draw();


protected:
    static b2World& m_rPhysWorld;
    static sf::RenderWindow& m_rWindow;

    b2Body* m_pBody;//pointer;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<DGModule> > m_DGModuleSPList;
    std::vector<std::tr1::shared_ptr<DModule> > m_DModuleSPList;
private:
};

#endif // DCHUNK_H
