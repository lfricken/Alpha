#include "Universe/Chunk.h"
#include <globals.h>

using namespace std;
b2World& Chunk::m_rPhysWorld = game.getGameUniverse().getWorld();
sf::RenderWindow& Chunk::m_rWindow = game.getGameWindow();

Chunk::Chunk()
{
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position = b2Vec2(0.0f, 0.0f);
    m_pBody = m_rPhysWorld.CreateBody(&m_bodyDef);
    m_pBody->SetUserData(this);
}
Chunk::Chunk(b2Vec2 coordinate, b2BodyType bodyType)
{
    m_bodyDef.type = bodyType;
    m_bodyDef.position = coordinate;
    m_pBody = m_rPhysWorld.CreateBody(&m_bodyDef);

    m_pBody->SetUserData(this);
}
Chunk::Chunk(const Chunk& old)
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
    /**Destroy all our module list, because the modules are preserved via SP **/
    //happens automatically
    /**Destroy our MultiTileMap, cause the textured verts should have been preserved via SP**/
    //This happens automatically.
    /**how do we delete our body??**/
    m_rPhysWorld.DestroyBody(m_pBody);
}


GModule* Chunk::getGModule(std::string targetName)
{
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        if((*it)->getTargetName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk " << m_targetName;
    return NULL;
}
Module* Chunk::getModule(std::string targetName)
{
    for(vector<tr1::shared_ptr<Module> >::const_iterator it = m_ModuleSPList.begin(); it != m_ModuleSPList.end(); ++it)
    {
        if((*it)->getTargetName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk " << m_targetName;
    return NULL;
}
IOBase* Chunk::getIOBase(std::string targetName)
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

        if(it_data->type == "GModule")
            ptr = static_cast<GModule*>(new GModule(*it_data));
        else
        {
            cout << "\nModule of type " << it_data->type << " was not found.";
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

        if(it_data->type == "Module")
            ptr = static_cast<Module*>(new Module(*it_data));
        else
        {
            cout << "\nModule of type " << it_data->type << " was not found.";
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
