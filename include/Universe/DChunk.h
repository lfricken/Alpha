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

    DChunk(const DChunk& old);
    virtual ~DChunk();

    virtual void add(std::vector<DGModuleData>& data);
    ///virtual void remove();//how to remove a module, if possible
    virtual b2Body* getBody();

    virtual void draw();

    /**CONST OVERLOADS**/
    virtual b2Body* getBody() const;
    virtual const b2BodyDef& getBodyDef() const;
    virtual const std::vector<std::tr1::shared_ptr<DGModule> >& getDGModuleSPList() const;
    virtual const std::vector<std::tr1::shared_ptr<DModule> >& getDModuleSPList() const;
    virtual const MultiTileMap& getTiles() const;

protected:
    static b2World& m_rPhysWorld;
    static sf::RenderWindow& m_rWindow;

    b2Body* m_pBody;//pointer;
    b2BodyDef m_bodyDef;///do we need to hold onto this?
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<DGModule> > m_DGModuleSPList;
    std::vector<std::tr1::shared_ptr<DModule> > m_DModuleSPList;
private:
};

#endif // DCHUNK_H
