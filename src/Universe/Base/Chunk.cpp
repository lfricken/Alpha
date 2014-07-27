#include "Chunk.h"
#include "globals.h"

#include "Intelligence.h"
#include "Sort.h"
#include "Angles.h"

#include "GModule.h"
#include "Module.h"

#include "Armor.h"
#include "ForceField.h"
#include "ForceFieldCore.h"
#include "Thruster.h"

using namespace std;

Chunk::Chunk() : IOBase(), m_rWindow(game.getGameWindow()), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    ChunkData data;
    f_initialize(data);
}
Chunk::Chunk(const ChunkData& data) : IOBase(static_cast<IOBaseData>(data)), m_rWindow(game.getGameWindow()), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    f_initialize(data);
}
Chunk::~Chunk()/**Don't destroy us in the middle of a physics step!**/
{
    breakControl();
    m_rPhysWorld.DestroyBody(m_pBody);
}
void Chunk::f_initialize(const ChunkData& data)
{
    m_maxZoom = data.maxZoom;
    m_minZoom = data.minZoom;

    m_bodyDef.bullet = data.isBullet;
    m_bodyDef.type = data.bodyType;
    m_bodyDef.position = data.position;
    m_controlEnabled = data.controlEnabled;

    m_pBody = m_rPhysWorld.CreateBody(&m_bodyDef);
    m_pBody->SetUserData(this);
    m_pController = NULL;
    m_hasController = false;

    m_awake = true;//regardless, set us to be awake
    if(!data.awake)//if it should be asleep
        sleep();//then cleanly put it to sleep


    m_fireTimer.setCountDown(0.1);///TEMPORARY
}
GModule* Chunk::getGModule(const std::string& targetName)
{
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        if((*it)->getName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk \"" << m_pIOComponent->getName() << "\":[" << m_pIOComponent->getID() << "]";
    ///ERROR LOG
    return NULL;
}
Module* Chunk::getModule(const std::string& targetName)
{
    for(vector<tr1::shared_ptr<Module> >::const_iterator it = m_ModuleSPList.begin(); it != m_ModuleSPList.end(); ++it)
    {
        if((*it)->getName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk \"" << m_pIOComponent->getName() << "\":[" << m_pIOComponent->getID() << "]";
    ///ERROR LOG
    return NULL;
}
IOBase* Chunk::getIOBase(const std::string& targetName)
{
    IOBase* ptr = getGModule(targetName);
    if(ptr != NULL)
        return ptr;

    return getModule(targetName);
}
GModule* Chunk::add(const vector<tr1::shared_ptr<GModuleData> >& rDataList)
{
    GModule* ptr;
    for(auto it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        ptr = (*it_data)->generate(this);
        InsertPtrVector(m_GModuleSPList, &IOBase::getID, tr1::shared_ptr<GModule>(ptr));
        m_tiles.add(ptr);///HERE IS WHERE WE WOULD give it a graphics component, instead of us a derived pointer from which it gets the base type
    }

    return ptr;
}
Module* Chunk::add(const vector<tr1::shared_ptr<ModuleData> >& rDataList)
{
    Module* ptr;
    for(auto it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        ptr = (*it_data)->generate(this);
        InsertPtrVector(m_ModuleSPList, &IOBase::getID, tr1::shared_ptr<Module>(ptr));
    }

    return ptr;
}
void Chunk::draw()
{
    if(m_awake)
    {
        auto it_end = m_GModuleSPList.end();
        for(auto it = m_GModuleSPList.begin(); it != it_end; ++it)
        {
            (*it)->animate();
        }

        m_tiles.setPosition(scale*m_pBody->GetPosition().x, scale*m_pBody->GetPosition().y);
        m_tiles.setRotation(leon::radToDeg(m_pBody->GetAngle()));
        m_rWindow.draw(m_tiles);
    }
}
void Chunk::physUpdate()//loop over all the special physics objects
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->physUpdate();
    }
    for(auto it = m_ModuleSPList.begin(); it != m_ModuleSPList.end(); ++it)
    {
        (*it)->physUpdate();
    }
}

/**IO-SYSTEM**/
void Chunk::toggleControl(bool state)//will or wont accept inputs from controllers
{
    m_controlEnabled = state;
}
bool Chunk::isControlEnabled() const
{
    return m_controlEnabled;
}
void Chunk::sleep()
{
    if(m_awake)//if we aren't already sleeping!
    {
        m_oldPos = m_pBody->GetPosition();//get our current data
        m_oldAngle = m_pBody->GetAngle();//radians

        m_pBody->SetActive(false);//remove from calculation
        m_pBody->SetAwake(false);//remove from updating
        toggleControl(false);

        m_pBody->SetLinearVelocity(b2Vec2(0,0));//cancel any movement
        m_pBody->SetAngularVelocity(0.0f);
        m_pBody->SetTransform(game.getGameUniverse().getBedFinder().getSleepPosition(), 0);//request new position from bedFinder
        m_awake = false;
    }
}
void Chunk::wake()
{
    if(!m_awake)//if we aren't awake
    {
        game.getGameUniverse().getBedFinder().free(m_pBody->GetPosition());

        m_pBody->SetActive(true);
        m_pBody->SetAwake(true);//remove from updating

        m_pBody->SetTransform(m_oldPos, m_oldAngle);//move us//radians
        toggleControl(true);
        m_awake = true;
    }
    else
    {
        cout << "\nWake Failed";
        ///error log
    }
}
void Chunk::wake(const b2Vec2& pos, float angle, const b2Vec2& velocity, float angVel)//box2d uses radians
{
    if(!m_awake)//if we aren't awake
    {
        game.getGameUniverse().getBedFinder().free(m_pBody->GetPosition());

        m_pBody->SetActive(true);
        m_pBody->SetAwake(true);

        m_pBody->SetTransform(pos, angle);//radians
        m_pBody->SetLinearVelocity(velocity);
        m_pBody->SetAngularVelocity(angVel);
        toggleControl(true);
        m_awake = true;
    }
    else
    {
        cout << "\nWake Failed";
        ///error log
    }

}
bool Chunk::isAwake() const
{
    return m_awake;
}
b2Body* Chunk::getBody()
{
    return m_pBody;
}
b2Body* Chunk::getBody() const
{
    return m_pBody;
}
const b2BodyDef& Chunk::getBodyDef() const
{
    return m_bodyDef;
}
const vector<tr1::shared_ptr<GModule> >& Chunk::getGModuleSPList() const
{
    return m_GModuleSPList;
}
const vector<tr1::shared_ptr<Module> >& Chunk::getModuleSPList() const
{
    return m_ModuleSPList;
}
const MultiTileMap& Chunk::getTiles() const
{
    return m_tiles;
}
void Chunk::primary(const b2Vec2& coords)
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->primary(coords);
    }

    ///get rid of this temporary stuff
    if(m_fireTimer.isTimeUp())
    {
        b2Vec2 difference(coords - m_pBody->GetPosition());
        float distance = sqrt(difference.x*difference.x + difference.y*difference.y);
        b2Vec2 component(difference.x/distance, difference.y/distance);

        float vel = 25;
        float off = 0;
        b2Vec2 velvec(vel*component.x, vel*component.y);
        b2Vec2 offset(off*component.x, off*component.y);

        Projectile* pBullet = game.getGameUniverse().getProjAlloc().getProjectile(0);
        pBullet->setLifeTimeRemain(3);
        pBullet->wake(m_pBody->GetPosition()+offset, atan(component.y/component.x), velvec+m_pBody->GetLinearVelocity(), m_pBody->GetAngularVelocity());//our position + some, no rotation, velocity +ours, our angular velocity
    }
}
void Chunk::secondary(const b2Vec2& coords)
{
    ///tell all our modules that we have secondaired at coords
    if(m_fireTimer.isTimeUp())
    {
        b2Vec2 difference(coords - m_pBody->GetPosition());
        float distance = sqrt(difference.x*difference.x + difference.y*difference.y);
        b2Vec2 component(difference.x/distance, difference.y/distance);

        float vel = 240;
        float off = 0;
        b2Vec2 velvec(vel*component.x, vel*component.y);
        b2Vec2 offset(off*component.x, off*component.y);

        Projectile* pBullet = game.getGameUniverse().getProjAlloc().getProjectile(1);
        pBullet->setLifeTimeRemain(3);
        pBullet->wake(m_pBody->GetPosition()+offset, atan(component.y/component.x), velvec+m_pBody->GetLinearVelocity(), m_pBody->GetAngularVelocity());//our position + some, no rotation, velocity +ours, our angular velocity
    }
}
void Chunk::aim(const b2Vec2& coords)
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->aim(coords);
    }
}
void Chunk::up()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->up();
    }
}
void Chunk::down()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->down();
    }
}
void Chunk::left()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->left();
    }
}
void Chunk::right()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->right();
    }
}
void Chunk::rollLeft()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->rollLeft();
    }
}
void Chunk::rollRight()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->rollRight();
    }
}
void Chunk::special_1()
{
    ///tell modules
}
void Chunk::special_2()
{
    ///tell modules
}
void Chunk::special_3()
{
    ///tell modules
}
void Chunk::special_4()
{
    ///tell modules

}
float Chunk::getMaxZoom() const
{
    return m_maxZoom;
}
float Chunk::getMinZoom() const
{
    return m_minZoom;
}
void Chunk::setGroupIndex(int group)
{
    ///ERROR LOG
    cout << "\nWtf are you doing??";
    /**loop over fixtures**/
    for (b2Fixture* fix = m_pBody->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Filter filter = fix->GetFilterData();
        filter.groupIndex = group;
        fix->SetFilterData(filter);
    }
}
/**CONTROL**/
Intelligence* Chunk::getController() const//done
{
    return m_pController;
}
bool Chunk::hasController() const//done
{
    return m_hasController;
}
void Chunk::linkControl(Intelligence* controller)
{
    f_setController(controller);
    m_pController->f_setTarget(this);
}
void Chunk::breakControl()//done
{
    if(m_hasController)
        m_pController->f_forgetTarget();

    f_forgetController();
}
void Chunk::f_forgetController()//done
{
    m_pController = NULL;
    m_hasController = false;
}
void Chunk::f_setController(Intelligence* controller)//done
{
    breakControl();
    m_pController = controller;
    m_hasController = true;
}
/**END**/
IOBaseReturn Chunk::input(IOBaseArgs)
{
    if(rCommand == "message")
    {
        std::string message;
        if(rInput >> message)
            std::cout << std::endl << m_pIOComponent->getName() << " has " << m_GModuleSPList.front()->getHealth() << " health, and received message: [" << message << "].";
        else
        {
            std::cout << "\nError in data extraction in input in GModule." << FILELINE;
            ///ERROR LOG
        }
    }
    else
    {
        std::cout << "\nError: [" << rCommand << "] was not recognized as a command." << FILELINE;
        ///ERROR LOG
    }
}
int Chunk::startContact(PhysicsBase* other)
{
    return 0;
}
int Chunk::endContact(PhysicsBase* other)
{
    return 0;
}
int Chunk::preSolveContact(PhysicsBase* other)
{
    return 0;
}
int Chunk::postSolveContact(PhysicsBase* other)
{
    return 0;
}
