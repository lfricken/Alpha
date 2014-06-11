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


    ///TEMPORARY
    m_fireTimer.setCountDown(0.1);
    m_accel = 50;
    m_torque = 50;
}
float Chunk::f_findRadius(std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList)
{
    float a, b, c, maxRadius = 1;
    for(vector<std::tr1::shared_ptr<GModuleData> >::iterator it = rDataList.begin(); it != rDataList.end(); ++it)
    {
        a = (*it)->offset.x;
        b = (*it)->offset.y;
        c = sqrt(a*a + b*b);
        if(c > maxRadius)
            maxRadius = c;
    }
    return maxRadius;
}
GModule* Chunk::getGModule(const std::string& targetName)
{
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        if((*it)->getName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk \"" << m_name << "\":[" << m_ID << "]";
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
    cout << "\nTarget " << targetName << " not found in chunk \"" << m_name << "\":[" << m_ID << "]";
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
/**
1. OUR LIST: Create GModules in our GModuleList
2. TILEMAP: Pass them to our MultiTileMap to be drawn later.
**/
void Chunk::add(const vector<tr1::shared_ptr<GModuleData> >& rDataList, const vector<b2Vec2>& vertices)
{
    ///THIS SHOULD BE DONE SOMEWHERE ELSE
    /**create our bounding box for large chunk collisions using vertices**/

    if(vertices.empty())
    {
        //don't create anything
    }
    else if(vertices.size() < 3)
    {
        //create a circle module with ship collision using f_findRadius

        /**
        float radius = f_findRadius(rDataList);
        m_shape = tr1::shared_ptr<b2Shape>(new b2CircleShape());
        std::static_pointer_cast<b2CircleShape>(m_shape)->m_p.Set(0, 0);
        std::static_pointer_cast<b2CircleShape>(m_shape)->m_radius = radius;
            m_shape.SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, data.rotation);//default
            m_fixtureDef.shape = &m_shape;//give our shape to our fixture definition
            m_fixtureDef.density = data.density;
            m_fixtureDef.friction = data.friction;
            m_fixtureDef.restitution = data.restitution;//setting our fixture data
            m_pBody = data.pBody;

            m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);**/

        /**Take our list of gmodule data and make real modules with it! rDataList**/
    }
    else
    {
        //create a Module with ship collisions with those coordinates
    }



    /**1**/
    for(vector<tr1::shared_ptr<GModuleData> >::const_iterator it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        GModule* ptr;
        (**it_data).pBody = m_pBody;

        if((**it_data).type == ClassType::GMODULE)
        {
            ptr = static_cast<GModule*>(new GModule(static_cast<GModuleData>(**it_data)));
        }
        else if((**it_data).type == ClassType::ARMOR)
        {
            GModuleData* pData = &(**it_data);
            ArmorData* pArmor = static_cast<ArmorData*>(pData);
            ptr = static_cast<GModule*>(new Armor(*pArmor));
        }
        else if((*it_data)->type == ClassType::FORCE)
        {
            GModuleData* pData = &(**it_data);
            ForceFieldCoreData* pFFCD = static_cast<ForceFieldCoreData*>(pData);

            ForceFieldData data;
            data.shape = Shape::CIRCLE;
            data.isSensor = true;
            data.halfSize = b2Vec2(8, 8);
            data.density = 0;
            data.pBody = m_pBody;
            data.categoryBits = Category::ShipForceField;
            data.maskBits = MaskBits::ShipForceField;

            ForceField* tempPtr = new ForceField(data);
            m_ModuleSPList.push_back(tr1::shared_ptr<Module>(tempPtr));
            m_SpecialPhysPList.push_back(tempPtr);

            pFFCD->pForceField = tempPtr;

            ptr = static_cast<GModule*>(new ForceFieldCore(*pFFCD));
            ///GET FORCE FIELD DATA FROM THE FORCE FIELD CORE DATA


            //tempPtr->disable();
        }
        ///list all types of GModules derivatives here


        else
        {
            cout << "\nModule of type " << (**it_data).type << " with name " << (**it_data).name <<  " was not found.";
            ///ERROR LOG
            ptr = static_cast<GModule*>(new GModule(*dynamic_pointer_cast<GModuleData>(*it_data)));
        }
        InsertPtrVector(m_GModuleSPList, &IOBase::getID, tr1::shared_ptr<GModule>(ptr));
    }


    /**TILEMAP: Create a Base Pointer List to pass to our tileMap**/
    vector<GraphicsBase*> gfxBasePList;
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it_derived = m_GModuleSPList.begin(); it_derived != m_GModuleSPList.end(); ++it_derived)
    {
        gfxBasePList.push_back(&(*(*it_derived)));
    }
    m_tiles.add(gfxBasePList);


    if(!rDataList.empty())/**Now, offset our origin by half the width of a tile, so that its center is also the center of the box's**/
        m_tiles.setOrigin(rDataList[0]->halfSize.x * scale , rDataList[0]->halfSize.y * scale);
    else
    {
        cout << "\nWARNING: Chunk::add()";
        ///ERROR LOG
    }
}
void Chunk::add(const vector<tr1::shared_ptr<ModuleData> >& rDataList)
{
    for(auto it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        Module* ptr;
        (*it_data)->pBody = m_pBody;

        if((*it_data)->type == ClassType::MODULE)
        {
            ptr = new Module(**it_data);
        }
        else if((*it_data)->type == ClassType::HULL)
        {
            ptr = new Module(**it_data);

            ModuleData hullSensorDat = **it_data;
            hullSensorDat.isSensor = true;
            hullSensorDat.categoryBits = Category::ShipHullSensor;
            hullSensorDat.maskBits = MaskBits::ShipHullSensor;
            hullSensorDat.butes.setBute(Butes::isDestructable, false);
            hullSensorDat.butes.setBute(Butes::isSolid, false);
            InsertPtrVector(m_ModuleSPList, &IOBase::getID, tr1::shared_ptr<Module>(new Module(hullSensorDat)));
        }
        else
        {
            ///ERROR LOG
            cout << "\nModule of type " << (*it_data)->type << " was not found.";
            ptr = new Module(**it_data);
        }
        InsertPtrVector(m_ModuleSPList, &IOBase::getID, tr1::shared_ptr<Module>(ptr));
    }
}
void Chunk::draw()
{
    if(m_awake)
    {
        m_tiles.setPosition(scale*m_pBody->GetPosition().x, scale*m_pBody->GetPosition().y);
        m_tiles.setRotation(leon::radToDeg(m_pBody->GetAngle()));
        m_rWindow.draw(m_tiles);
    }
}
void Chunk::physUpdate()//loop over all the special physics objects
{
    for(vector<PhysicsBase*>::iterator it = m_SpecialPhysPList.begin(); it != m_SpecialPhysPList.end(); ++it)
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
        m_pBody->SetTransform(game.getGameUniverse().getBedFinder().getSleepPosition(), 0);///request new position from bedFinder
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
void Chunk::primary(sf::Vector2f coords)
{
    ///tell all our modules that we have primaried at those coords

    ///get rid of this temporary stuff
    if(m_fireTimer.isTimeUp())
    {
        b2Vec2 difference(coords.x/scale - m_pBody->GetPosition().x, coords.y/scale - m_pBody->GetPosition().y);
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
void Chunk::secondary(sf::Vector2f coords)
{
    ///tell all our modules that we have secondaired at coords
    if(m_fireTimer.isTimeUp())
    {
        b2Vec2 difference(coords.x/scale - m_pBody->GetPosition().x, coords.y/scale - m_pBody->GetPosition().y);
        float distance = sqrt(difference.x*difference.x + difference.y*difference.y);
        b2Vec2 component(difference.x/distance, difference.y/distance);

        float vel = 50;
        float off = 0;
        b2Vec2 velvec(vel*component.x, vel*component.y);
        b2Vec2 offset(off*component.x, off*component.y);

        Projectile* pBullet = game.getGameUniverse().getProjAlloc().getProjectile(1);
        pBullet->setLifeTimeRemain(3);
        pBullet->wake(m_pBody->GetPosition()+offset, atan(component.y/component.x), velvec+m_pBody->GetLinearVelocity(), m_pBody->GetAngularVelocity());//our position + some, no rotation, velocity +ours, our angular velocity
    }
}
void Chunk::aim(sf::Vector2f coords)
{
///tell modules
}
void Chunk::up()
{
    ///tell modules
    m_pBody->ApplyForceToCenter(b2Vec2(m_accel*m_pBody->GetMass()*sin(m_pBody->GetAngle()),-m_accel*m_pBody->GetMass()*cos(m_pBody->GetAngle())), true);
}
void Chunk::down()
{
    ///tell modules
}
void Chunk::left()
{
    ///tell modules
}
void Chunk::right()
{
    ///tell modules
}
void Chunk::rollLeft()
{
    ///tell modules
}
void Chunk::rollRight()
{
    ///tell modules
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
IOBaseReturn Chunk::input_1(IOBaseArgs)
{
    std::string n;
    if(!(rInput >> n))
    {
        cout << "\nExtraction Fail.";
        ///ERROR LOG
    }
    std::cout << std::endl << m_name << " has " << m_GModuleSPList.front()->getHealth() << " health, also " << n;
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

/*
void Chunk::add(vector<tr1::shared_ptr<GModuleData> >& rDataList)
{
    //Take our list of gmodule data and make real modules with it! rDataList
    for(vector<tr1::shared_ptr<GModuleData> >::iterator it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        GModule* ptr;
        (*it_data)->pBody = m_pBody;

        if((*it_data)->type == ClassType::GMODULE)
            ptr = new GModule(**it_data);

        ///list all types of modules here


        else
        {
            cout << "\nModule of type " << (*it_data)->type << " with name " << (*it_data)->name <<  " was not found.";
            ///ERROR LOG
            ptr = new GModule(**it_data);
        }
        m_GModuleSPList.push_back(tr1::shared_ptr<GModule>(ptr));
    }


    //TILEMAP: Create a Base Pointer List to pass to our tileMap
    vector<GraphicsBase*> gfxBasePList;
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it_derived = m_GModuleSPList.begin(); it_derived != m_GModuleSPList.end(); ++it_derived)
    {
        gfxBasePList.push_back(&(*(*it_derived)));
    }
    m_tiles.add(gfxBasePList);


    if(!rDataList.empty())//Now, offset our origin by the appropriate amount indicated by the physData
        m_tiles.setOrigin(rDataList[0]->halfSize.x * scale , rDataList[0]->halfSize.y * scale);
    else
        cout << "\nWARNING: Chunk::add()";
}
*/





/*
Chunk::Chunk(const Chunk& old) : m_rWindow(game.getGameWindow()), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    cout << "\nChunk Copy Called...";
    m_pBody = old.getBody();
    m_bodyDef = old.getBodyDef();
    m_tiles = old.getTiles();
    m_GModuleSPList = old.getGModuleSPList();
    m_ModuleSPList = old.getModuleSPList();
    cout << "Completed.";
}
*/
