#ifndef DCHUNK_H
#define DCHUNK_H

#include "stdafx.h"
#include "MultiTileMap.h"

class GModule;
struct GModuleData;
class Module;
struct ModuleData;
class Intelligence;

struct ChunkData
{
    IOBaseData baseData;
    b2BodyType bodyType;
    b2Vec2 position;
    bool isBullet;
};

class Chunk : public IOBase
{
public:
    Chunk();
    Chunk(const ChunkData& data);
    Chunk(const Chunk& old);///should this exist?
    virtual ~Chunk();//Don't destroy us in the middle of a physics step


    virtual b2Body* getBody();

    virtual GModule* getGModule(const std::string& targetName);
    virtual Module* getModule(const std::string& targetName);
    virtual IOBase* getIOBase(const std::string& targetName);

    virtual void add(std::vector<GModuleData>& data);//we only call this once!
    virtual void add(std::vector<ModuleData>& data);//we only call this once!

    virtual void draw();


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

    /**CONTROL**/
    Intelligence* getController() const;
    bool hasController() const;
    void linkControl(Intelligence* controller);
    void breakControl();

    /**CONST OVERLOADS**/
    virtual b2Body* getBody() const;
    virtual const b2BodyDef& getBodyDef() const;
    virtual const std::vector<std::tr1::shared_ptr<GModule> >& getGModuleSPList() const;
    virtual const std::vector<std::tr1::shared_ptr<Module> >& getModuleSPList() const;
    virtual const MultiTileMap& getTiles() const;

    /**OVERRIDE**/
    virtual void input_1(sf::Packet& rInput);

protected:
    b2World& m_rPhysWorld;
    sf::RenderWindow& m_rWindow;

    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;

    float m_accel, m_torque;///move these to a derivative of chunk

private:
    void f_initialize(const ChunkData& data);

    friend class Intelligence;
    void f_forgetController();//CONTROL
    void f_setController(Intelligence* controller);
    Intelligence* m_pController;//this is a pointer to our controller
    bool m_hasController;
};

#endif // DCHUNK_H
