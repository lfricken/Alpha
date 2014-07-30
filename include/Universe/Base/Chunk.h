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
        defaultMaxEnergy(0),
        maxMaxZoom(128),
        defaultMaxZoom(128),
        minZoom(0.5),
        controlEnabled(def::cnk::controlEnabled),
        awake(true)///need a default state here
    {
        type = ClassType::CHUNK;
    }

    ///be able to add a texture here so we can have big space ship sprites
    b2BodyType bodyType;
    b2Vec2 position;
    bool isBullet;

    T_Energy defaultMaxEnergy;

    T_Zoom maxMaxZoom;
    T_Zoom defaultMaxZoom;
    T_Zoom minZoom;

    bool controlEnabled;
    bool awake;
};

class Chunk : public IOBase
{
public:
    Chunk(const ChunkData& rData);
    virtual ~Chunk();//Don't destroy us in the middle of a physics step

    /**GET MODULES**/
    GModule* getGModule(const std::string& targetName);
    Module* getModule(const std::string& targetName);
    IOBase* getIOBase(const std::string& targetName);

    /**ADD MODULES**////SHOULD ADD A SINGLE ONE, AND A LIST
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

    /**Variables**/
    ZoomPool& getZoomPool();
    EnergyPool& getEnergyPool();

    /**GRAPHICS**/
    void draw();

    /**IO-SYSTEM**/
    virtual IOBaseReturn input(IOBaseArgs);

protected:
    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;
    std::vector<std::tr1::shared_ptr<Weapon> > m_WeaponSPList;

private:
    std::tr1::shared_ptr<ZoomPool> m_spZoomPool;
    std::tr1::shared_ptr<EnergyPool> m_spEnergyPool;
    std::tr1::shared_ptr<Link<Chunk, Intelligence> > m_spLinker;

    bool m_controlEnabled;

    bool m_awake;

    b2Vec2 m_oldPos;//used for sleep
    float m_oldAngle;
};

#endif // DCHUNK_H
