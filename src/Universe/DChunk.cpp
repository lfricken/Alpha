#include "Universe/DChunk.h"
#include <globals.h>

using namespace std;
b2World& DChunk::m_rPhysWorld = game.getGameUniverse().getWorld();
sf::RenderWindow& DChunk::m_rWindow = game.getGameWindow();

DChunk::DChunk()
{
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position = b2Vec2(0.0f, 0.0f);
    m_pBody = m_rPhysWorld.CreateBody(&m_bodyDef);
    m_pBody->SetUserData(this);
}
DChunk::DChunk(b2Vec2 coordinate)
{
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position = coordinate;
    m_pBody = m_rPhysWorld.CreateBody(&m_bodyDef);

    m_pBody->SetUserData(this);
}
DChunk::DChunk(const DChunk& old)
{
    cout << "\nDChunk Copy Called...";
    m_pBody = old.getBody();
    m_bodyDef = old.getBodyDef();
    m_tiles = old.getTiles();
    m_DGModuleSPList = old.getDGModuleSPList();
    m_DModuleSPList = old.getDModuleSPList();
    cout << "Completed.";
}
DChunk::~DChunk()
{
    cout << "\nDChunk Dtor Called...";
    /**Destroy all our modules in both vectors**/
    //happens automatically
    /**Destroy our MultiTileMap**/
    //This happens automatically.
    /**Finally, destroy our body, and all the fixtures on it**/
   /// m_rPhysWorld.DestroyBody(m_pBody);//we only want to call this sometimes
    cout << "Completed.";
}
/**
1. Create DGModules in our dgModuleList
2. Pass them to tilemap to be drawn later.
**/
void DChunk::add(vector<DGModuleData>& rDataList)
{
    /**Take our list of module data and make real modules with it!**/
    for(vector<DGModuleData>::iterator it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        it_data->physicsData.pBody = m_pBody;
        m_DGModuleSPList.push_back(tr1::shared_ptr<DGModule>(new DGModule(*it_data)));
    }


    /**Create a Base Pointer List to pass to our tileMap**/
    vector<GraphicsBase*> gfxBasePList;
    for(std::vector<std::tr1::shared_ptr<DGModule> >::const_iterator it_derived = m_DGModuleSPList.begin(); it_derived != m_DGModuleSPList.end(); ++it_derived)
    {
        gfxBasePList.push_back(&(*(*it_derived)));
    }
    m_tiles.add(gfxBasePList);


    if(!rDataList.empty())///wtf is this doing? accessing the first element of something with 0 elements?????
        m_tiles.setOrigin(rDataList[0].physicsData.halfSize.x * scale , rDataList[0].physicsData.halfSize.y * scale);
    else
        cout << "\nWARNING: DChunk::add()";//debug
}
void DChunk::draw()
{
    m_tiles.setPosition(scale*m_pBody->GetPosition().x, scale*m_pBody->GetPosition().y);
    m_tiles.setRotation(180.0*m_pBody->GetAngle()/PI);
    m_rWindow.draw(m_tiles);
}
b2Body* DChunk::getBody()
{
    return m_pBody;
}
b2Body* DChunk::getBody() const
{
    return m_pBody;
}
const b2BodyDef& DChunk::getBodyDef() const
{
    return m_bodyDef;
}
const vector<tr1::shared_ptr<DGModule> >& DChunk::getDGModuleSPList() const
{
    return m_DGModuleSPList;
}
const vector<tr1::shared_ptr<DModule> >& DChunk::getDModuleSPList() const
{
    return m_DModuleSPList;
}
const MultiTileMap& DChunk::getTiles() const
{
    return m_tiles;
}
