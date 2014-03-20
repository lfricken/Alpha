#include "Chunk.h"
#include "globals.h"

#include "Intelligence.h"
#include "GModule.h"
#include "Module.h"

using namespace std;

Chunk::Chunk() : m_rWindow(game.getGameWindow()), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    ChunkData data;
    data.isBullet = false;
    data.bodyType = b2_dynamicBody;
    data.position = b2Vec2(0.0f, 0.0f);
    f_initialize(data);
}
Chunk::Chunk(const ChunkData& data) : m_rWindow(game.getGameWindow()), m_rPhysWorld(game.getGameUniverse().getWorld()), IOBase(data.baseData)
{
    f_initialize(data);
}
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
Chunk::~Chunk()/**Don't destroy us in the middle of a physics step!**/
{
    m_rPhysWorld.DestroyBody(m_pBody);
    breakControl();
}
void Chunk::f_initialize(const ChunkData& data)
{
    m_bodyDef.bullet = data.isBullet;
    m_bodyDef.type = data.bodyType;
    m_bodyDef.position = data.position;

    m_pBody = m_rPhysWorld.CreateBody(&m_bodyDef);
    m_pBody->SetUserData(this);
    m_pController = NULL;
    m_hasController = false;

    ///TEMPORARY
    m_accel = 50;
    m_torque = 50;
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
void Chunk::add(vector<GModuleData>& rDataList)
{
    /**OUR LIST: Take our list of module data and make real modules with it!**/
    for(vector<GModuleData>::iterator it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        GModule* ptr;
        it_data->physicsData.pBody = m_pBody;

        if(it_data->baseData.type == "GModule")
            ptr = static_cast<GModule*>(new GModule(*it_data));

        ///list all types here


        else
        {
            cout << "\nModule of type " << it_data->baseData.type << " was not found.";
            ///ERROR LOG
            ptr = new GModule(*it_data);
        }
        m_GModuleSPList.push_back(tr1::shared_ptr<GModule>(ptr));
    }


    /**TILEMAP: Create a Base Pointer List to pass to our tileMap**/
    vector<GraphicsBase*> gfxBasePList;
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it_derived = m_GModuleSPList.begin(); it_derived != m_GModuleSPList.end(); ++it_derived)
    {
        gfxBasePList.push_back(&(*(*it_derived)));
    }
    m_tiles.add(gfxBasePList);


    if(!rDataList.empty())/**Now, offset our origin by the appropriate amount indicated by the physData**/
        m_tiles.setOrigin(rDataList[0].physicsData.halfSize.x * scale , rDataList[0].physicsData.halfSize.y * scale);
    else
        cout << "\nWARNING: Chunk::add()";
}
void Chunk::add(vector<ModuleData>& rDataList)
{
    for(vector<ModuleData>::iterator it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        Module* ptr;
        it_data->physicsData.pBody = m_pBody;

        if(it_data->baseData.type == "Module")
            ptr = static_cast<Module*>(new Module(*it_data));
        else
        {
            cout << "\nModule of type " << it_data->baseData.type << " was not found.";
            ptr = new Module(*it_data);
        }
        m_ModuleSPList.push_back(tr1::shared_ptr<Module>(ptr));
    }
}
void Chunk::draw()
{
    m_tiles.setPosition(scale*m_pBody->GetPosition().x, scale*m_pBody->GetPosition().y);
    m_tiles.setRotation(180.0*m_pBody->GetAngle()/PI);
    m_rWindow.draw(m_tiles);
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

}
void Chunk::secondary(sf::Vector2f coords)
{

}
void Chunk::aim(sf::Vector2f coords)
{

}
void Chunk::up()
{
    m_pBody->ApplyForceToCenter(b2Vec2(m_accel*m_pBody->GetMass()*sin(m_pBody->GetAngle()),-m_accel*m_pBody->GetMass()*cos(m_pBody->GetAngle())), true);
}

void Chunk::down()
{

}
void Chunk::left()
{

}
void Chunk::right()
{

}
void Chunk::rollLeft()
{

}
void Chunk::rollRight()
{

}
void Chunk::special_1()
{

}
void Chunk::special_2()
{

}
void Chunk::special_3()
{

}
void Chunk::special_4()
{

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

void Chunk::input_1(sf::Packet& rInput)
{
    std::string n;
    rInput >> n;
    std::cout << std::endl << m_name << " has " << m_GModuleSPList.front()->getHealth() << " health, also " << n;
}
