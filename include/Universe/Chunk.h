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
    virtual ~Chunk();//Don't destroy us in the middle of a physics step

    virtual b2Body* getBody();

    virtual GModule* getGModule(std::string targetName);
    virtual Module* getModule(std::string targetName);
    virtual IOBase* getIOBase(std::string targetName);

    virtual void add(std::vector<GModuleData>& data);//we only call this once!
    virtual void add(std::vector<ModuleData>& data);//we only call this once!

    virtual void draw();

    ///virtual void remove();//how to remove a module, if possible?

    /**INPUT**/
    virtual void primary(sf::Vector2f coords);
    virtual void secondary(sf::Vector2f coords);
    virtual void aim(sf::Vector2f coords);
    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    virtual void rollLeft();
    virtual void rollRight();
    virtual void special_1();
    virtual void special_2();
    virtual void special_3();
    virtual void special_4();



    /**CONST OVERLOADS**/
    virtual b2Body* getBody() const;
    virtual const b2BodyDef& getBodyDef() const;
    virtual const std::vector<std::tr1::shared_ptr<GModule> >& getGModuleSPList() const;
    virtual const std::vector<std::tr1::shared_ptr<Module> >& getModuleSPList() const;
    virtual const MultiTileMap& getTiles() const;

protected:
    static b2World& m_rPhysWorld;
    sf::RenderWindow& m_rWindow;

    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;


    float m_accel, m_torque;
private:
};

#endif // DCHUNK_H
