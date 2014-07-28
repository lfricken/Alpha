#ifndef DCHUNK_H
#define DCHUNK_H

#include "stdafx.h"
#include "MultiTileMap.h"

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

    ///be able to add a texture here so we can have big space ships
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

    virtual b2Body* getBody();

    GModule* getGModule(const std::string& targetName);
    Module* getModule(const std::string& targetName);
    IOBase* getIOBase(const std::string& targetName);
    IOBase* getIOBase(unsigned int id);

    ///  virtual void add(std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList);
    virtual GModule* add(const std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList);//returns the last GModule added
    virtual Module* add(const std::vector<std::tr1::shared_ptr<ModuleData> >& data);//returns the last Module added
    virtual Weapon* add(const WeaponData& rData);

    /**IO-SYSTEM**/
    virtual IOBaseReturn input(IOBaseArgs);


    /**PHYSICS**/
    virtual int startContact(PhysicsBase* other);
    virtual int endContact(PhysicsBase* other);
    virtual int preSolveContact(PhysicsBase* other);
    virtual int postSolveContact(PhysicsBase* other);
    virtual void setGroupIndex(int group);

    void sleep();//sets body to sleep, sets all velocities to 0, and goes to coord args
    void wake();
    virtual void wake(const b2Vec2& pos, float angle, const b2Vec2& velocity, float angVel);
    bool isAwake() const;


    /**INPUT**/
    virtual void primary(const b2Vec2& coords);
    virtual void secondary(const b2Vec2& coords);
    virtual void aim(const b2Vec2& coords);
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

    void toggleControl(bool state);//will or wont accept inputs from controllers
    bool isControlEnabled() const;

    virtual float getMaxZoom() const;
    virtual float getMinZoom() const;


    /**CONST OVERLOADS**/
    b2Body* getBody() const;
    const b2BodyDef& getBodyDef() const;
    const std::vector<std::tr1::shared_ptr<GModule> >& getGModuleSPList() const;
    const std::vector<std::tr1::shared_ptr<Module> >& getModuleSPList() const;
    const MultiTileMap& getTiles() const;


    /**UPDATE**/
    virtual void draw();
    virtual void physUpdate();

protected:
    sf::RenderWindow& m_rWindow;
    b2World& m_rPhysWorld;

    float m_maxZoom;///used by controller to limit zoom levels maybe this should be somewhere else?
    float m_minZoom;

    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;
    std::vector<std::tr1::shared_ptr<Weapon> > m_WeaponSPList;
    std::vector<std::tr1::shared_ptr<sf::Sprite> > m_Sprites;///THESE SHOULD BE DECORATIONS, NOT RAW SPRITES
private:
    virtual void f_initialize(const ChunkData& data);

    friend class Intelligence;
    void f_forgetController();//CONTROL
    void f_setController(Intelligence* controller);
    Intelligence* m_pController;//this is a pointer to our controller
    bool m_hasController;
    bool m_controlEnabled;
    bool m_awake;

    b2Vec2 m_oldPos;
    float m_oldAngle;
};

#endif // DCHUNK_H
