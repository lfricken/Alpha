#ifndef DCHUNK_H
#define DCHUNK_H

#include <stdafx.h>
#include <Universe/GModule.h>
#include <Universe/Module.h>
#include <Universe/MultiTileMap.h>

class Chunk : public IOBase
{
public:
    Chunk();
    Chunk(b2Vec2 coordinate, b2BodyType bodyType = b2_dynamicBody);

    Chunk(const Chunk& old);
    virtual ~Chunk();/**Don't destroy us in the middle of a physics step!**/

    virtual b2Body* getBody();

    virtual void add(std::vector<GModuleData>& data);/**we only call this once!**/
    virtual void add(std::vector<ModuleData>& data);/**we only call this once!**/

    virtual void draw();

    ///virtual void remove();//how to remove a module, if possible?




    /**CONST OVERLOADS**/
    virtual b2Body* getBody() const;
    virtual const b2BodyDef& getBodyDef() const;
    virtual const std::vector<std::tr1::shared_ptr<GModule> >& getGModuleSPList() const;
    virtual const std::vector<std::tr1::shared_ptr<Module> >& getModuleSPList() const;
    virtual const MultiTileMap& getTiles() const;

protected:
    static b2World& m_rPhysWorld;
    static sf::RenderWindow& m_rWindow;

    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;
private:
};

#endif // DCHUNK_H
