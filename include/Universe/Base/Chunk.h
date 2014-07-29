#ifndef DCHUNK_H
#define DCHUNK_H

#include "stdafx.h"
#include "MultiTileMap.h"
#include "VariableNames.h"
#include "Link.h"

class GModule;
struct GModuleData;
class Module;
struct ModuleData;
class Weapon;
struct WeaponData;

class PhysicsBase;
class Intelligence;

struct ChunkData : public IOBaseData//initialized
{
    ChunkData() :
        IOBaseData(),
        bodyType(def::cnk::bodyType),
        position(def::cnk::position),
        isBullet(def::cnk::isBullet),
        maxZoom(def::cnk::maxZoom),
        minZoom(def::cnk::minZoom),
        controlEnabled(def::cnk::controlEnabled),
        awake(true)///need a default state here
    {
        type = ClassType::CHUNK;
    }

    ///be able to add a texture here so we can have big space ship sprites
    b2BodyType bodyType;
    b2Vec2 position;
    bool isBullet;
    float maxZoom;
    float minZoom;
    bool controlEnabled;
    bool awake;
};

class Chunk : public IOBase
{
public:
    Chunk();
    Chunk(const ChunkData& data);
    virtual ~Chunk();//Don't destroy us in the middle of a physics step



    /**GET MODULES**/
    GModule* getGModule(const std::string& targetName);
    Module* getModule(const std::string& targetName);
    IOBase* getIOBase(const std::string& targetName);

    /**ADD MODULES**/
    GModule* add(const std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList);//returns the last GModule added
    Module* add(const std::vector<std::tr1::shared_ptr<ModuleData> >& data);//returns the last Module added
    Weapon* add(const WeaponData& rData);


    /**PHYSICS**/
    virtual int startContact(PhysicsBase* other);
    virtual int endContact(PhysicsBase* other);
    virtual int preSolveContact(PhysicsBase* other);
    virtual int postSolveContact(PhysicsBase* other);
    b2Body* getBody();
    virtual void physUpdate();

    ///CONSIDER MAKING THIS A COMPONENT
    void sleep();//sets body to sleep, sets all velocities to 0, and goes to coord args
    void wake();
    virtual void wake(const b2Vec2& pos, float angle, const b2Vec2& velocity, float angVel);
    bool isAwake() const;


    /**INPUT**/
    void primary(const b2Vec2& coords);
    void secondary(const b2Vec2& coords);
    void aim(const b2Vec2& coords);
    void up();
    void down();
    void left();
    void right();
    void rollLeft();
    void rollRight();
    void special_1();
    void special_2();
    void special_3();
    void special_4();


    /**CONTROL**/
    Link<Chunk, Intelligence>& getLinker();
    void toggleControl(bool state);//will or wont accept inputs from controllers
    bool isControlEnabled() const;

    float getMaxZoom() const;///REPLACE WITH ZOOM VARIABLE
    float getMinZoom() const;


    /**GRAPHICS**/
    void draw();


    /**IO-SYSTEM**/
    virtual IOBaseReturn input(IOBaseArgs);

protected:

    float m_maxZoom;///used by controller to limit zoom levels maybe this should be a VariableTM
    float m_minZoom;

    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;
    std::vector<std::tr1::shared_ptr<Weapon> > m_WeaponSPList;
private:
    virtual void f_initialize(const ChunkData& data);

    EnergyPool m_energyPool;

    Link<Chunk, Intelligence> m_linker;
    bool m_controlEnabled;

    bool m_awake;

    b2Vec2 m_oldPos;
    float m_oldAngle;
};

#endif // DCHUNK_H
