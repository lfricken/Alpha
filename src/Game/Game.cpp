/**WONT BE NEEDED**/
#include "Chunk.h"
#include "Ship.h"

#include "GModule.h"
#include "Module.h"
/**WONT BE NEEDED**/

#include "Game.h"
#include "globals.h"
#include "IOManager.h"
#include "ControlManager.h"
#include "BaseFunctionFinder.h"

using namespace std;

Game::Game()
{
    ///load window data into settings, and launch window with the settings
    m_settings.antialiasingLevel = 4;
    m_spWindow = std::tr1::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1600, 900), "SFML Box2D Test Environment", sf::Style::Default, m_settings));
    m_spFunctionFinder = std::tr1::shared_ptr<BaseFunctionFinder>(new BaseFunctionFinder);//independent
    m_spTexAlloc = std::tr1::shared_ptr<TextureAllocator>(new TextureAllocator());//independent
    m_spOverlayManager = std::tr1::shared_ptr<OverlayManager>(new OverlayManager());//independent
    m_spUniverse = std::tr1::shared_ptr<Universe>(new Universe());//independent
    /**created last**/
    m_spControlManager = std::tr1::shared_ptr<ControlManager>(new ControlManager);//needs Window and Universe
    m_spIOManager = std::tr1::shared_ptr<IOManager>(new IOManager(*this));//requires Universe and OverlayManager
    m_spGui = std::tr1::shared_ptr<tgui::Gui>(new tgui::Gui(*m_spWindow));


    bool loadedVsinc = true;
    int loadedFrameRate = 60;///called that because we are supposed to load that
    std::string loadedFont = "TGUI/fonts/DejaVuSans.ttf";

    m_spGui->setGlobalFont(loadedFont);
    m_spWindow->setVerticalSyncEnabled(loadedVsinc);
    m_spWindow->setFramerateLimit(loadedFrameRate);
    m_spFunctionFinder->load("functionTable.tbl");
    ///This code won't work! WTF?
    ///if(!icon.loadFromFile("textures/tileset.png"))
    /// cout << "\nIcon Load Error";///texture allocator
    ///m_spWindow.setIcon(32, 32, icon.getPixelsPtr());
}
Game::~Game()//unfinished
{

}
IOManager& Game::getGameIOManager()
{
    return *m_spIOManager;
}
sf::RenderWindow& Game::getGameWindow()
{
    return *m_spWindow;
}
TextureAllocator& Game::getTextureAllocator()
{
    return *m_spTexAlloc;
}
Universe& Game::getGameUniverse()
{
    return *m_spUniverse;
}
OverlayManager& Game::getGameOverlayManager()
{
    return *m_spOverlayManager;
}
BaseFunctionFinder& Game::getGameFunctionFinder()
{
    return *m_spFunctionFinder;
}
Game::Status Game::client()
{
    return run();
}
Game::Status Game::server()
{
    return run();
}
Game::Status Game::local()
{
    return run();
}
Game::Status Game::run()
{
    f_load("stuff");
    cout << "\nLoad";

    /**SIMULATION & RUNTIME**/
    Game::Status newState = Game::Local;
    sf::Clock clock;
    float fps = 0;
    float firstTime = 0, secondTime = 0, timeForFrame = 0, computeTime = 0, remainder = 0;
    int i = 0;

    sf::Event event;
    while (m_spWindow->isOpen() && newState != Game::Quit)
    {
        secondTime = clock.getElapsedTime().asSeconds();
        timeForFrame = secondTime - firstTime;
        computeTime = timeForFrame + remainder;
        fps = 1.0/timeForFrame;
        firstTime = clock.getElapsedTime().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            cout << "\nFPS: " << fps;

        /**INPUT and PHYSICS**/

        while (m_spWindow->pollEvent(event))
        {
            m_spGui->handleEvent(event);
            if(m_spControlManager->choiceUpdate(event))//if we put this before physstep, the camera lags!
                newState = Game::Quit;
        }
        while(computeTime > 0 && i < 6)///should max iterations depend on how far we are behind?
        {
            ++i;
            m_spControlManager->pressedUpdate();
            computeTime -= m_spUniverse->physStep();
        }
        remainder = computeTime;
        i = 0;
        if(remainder > 0)
            cout << endl << remainder;


        m_spIOManager->update(timeForFrame);

        /**DRAW**/
        m_spWindow->clear();
        m_spControlManager->drawUpdate();

        m_spWindow->setView(m_spWindow->getDefaultView());//draw stuff that is on hud
        m_spGui->draw();

        m_spWindow->display();

    }
    return newState;
}




void Game::f_load(const std::string& stuff)///ITS NOT CLEAR WHAT WE ARE LOADING EXACTLY
{

    ///Go through file sections
    ///Intelligences
    ///Universe Entities
    ///Menu Items???

    /**
    IF TYPE = SOMETHING
        BaseChunk* = NEW SOMETHING
    ELSE IF TYPE = SOMETHING ELSE
        BaseChunk* = NEW SOMETHING ELSE

    add things to this thing...
    push into universe or GUI thing...
    repeat**/
    /**=============================================GUI=============================================**/
    std::string config = "TGUI/widgets/Black.conf";

    /**TAB**/
    tgui::Tab::Ptr tab(*m_spGui);
    tab->load(config);
    tab->setPosition(10, 10);
    tab->add("Weapon");
    tab->add("Ammo");
    tab->add("Items");
    /**TAB**/


    /**=============================================GUI=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================STATIC=============================================**/

    std::vector<b2Vec2> example;

    /**STATIC MODULES**/
    vector<GModuleData> staticGModuleDataList;
    GModuleData solidFixtureData;
    solidFixtureData.type = ClassType::GMODULE;

    solidFixtureData.spCourierList.push_back( tr1::shared_ptr<Courier>(new Courier()) );
    Courier& cor = *solidFixtureData.spCourierList.front();
    sf::Packet pack;
    pack << "test";
    cor.condition.reset(HEALTH, "97", 97, '<', true);
    cor.package.reset("Static_Chunk_1", "input_1", pack, 1, Destination::UNIVERSE);
    m_allCouriers.push_back(&cor);

    solidFixtureData.isSensor = false;
    solidFixtureData.shape = Shape::Octagon;
    solidFixtureData.density = 1.0f;
    solidFixtureData.friction = 0.4f;
    solidFixtureData.halfSize = b2Vec2(2, 5);
    solidFixtureData.offset = b2Vec2(0, 0);
    solidFixtureData.pBody = NULL;//we dont know it yet
    solidFixtureData.restitution = 0.2f;
    solidFixtureData.rotation = 0.0f;
    solidFixtureData.texName = "textures/tileset.png";
    solidFixtureData.texTile = sf::Vector2f(0, 0);
    solidFixtureData.texTileSize = sf::Vector2f(64, 64);
    solidFixtureData.color = sf::Color::Red;

    staticGModuleDataList.push_back(solidFixtureData);
    /**STATIC MODULES**/

    /**STATIC CHUNK**/
    ChunkData staticChunkData;
    staticChunkData.position = b2Vec2(-20,-20);
    staticChunkData.isEnabled = true;
    staticChunkData.bodyType = b2BodyType::b2_staticBody;
    staticChunkData.isBullet = false;
    staticChunkData.name = "Static_Chunk_1";

    Chunk* staticChunk = new Chunk(staticChunkData);
    staticChunk->add(staticGModuleDataList, example);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(staticChunk));
    /**STATIC CHUNK**/

    /**=============================================STATIC=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================SHIPS=============================================**/



    /**SHIP MODULES**/
    GModuleData shipModuleData;
    shipModuleData.type = ClassType::GMODULE;
    shipModuleData.shape = Shape::Box;
    shipModuleData.categoryBits = CollisionCategory::ShipModule;
    shipModuleData.maskBits = CollisionCategory::Projectile;
    shipModuleData.isSensor = false;
    shipModuleData.density = 1.0f;
    shipModuleData.friction = 0.4f;
    shipModuleData.halfSize = b2Vec2(0.25, 0.25);
    shipModuleData.offset = b2Vec2(0, 0);
    shipModuleData.pBody = NULL;//we dont know it yet
    shipModuleData.restitution = 0.2f;
    shipModuleData.rotation = 0.0f;
    shipModuleData.texName = "textures/tileset.png";
    shipModuleData.texTile = sf::Vector2f(0, 0);
    shipModuleData.texTileSize = sf::Vector2f(64, 64);
    shipModuleData.color = sf::Color::White;

    ModuleData mdata;
    mdata.type = ClassType::MODULE;
    mdata.density = 1.0f;
    mdata.friction = 0.4f;
    mdata.halfSize = b2Vec2(0.25, 0.25);
    mdata.offset = b2Vec2(0, -5);
    mdata.pBody = NULL;//we dont know it yet
    mdata.restitution = 0.2f;
    mdata.rotation = 0.0f;

    ///WE NEED TO GET A STANDARD SIZE??
    vector<GModuleData> moduleList1;
    vector<ModuleData> moduleList2;
    short int texTile = 0;
    float offsetDelta = 2*shipModuleData.halfSize.x;
    for (float i=0, x=-2, numBoxsX = 9; i<numBoxsX; ++i, x+=offsetDelta)//creates boxes in a line
    {
        for (float c=0, y=-4.5, numBoxsY = 19; c<numBoxsY; ++c, y+=offsetDelta, ++texTile)
        {
            if (texTile == 4)
                texTile = 0;
            shipModuleData.offset.x = x;
            shipModuleData.offset.y = y;
            shipModuleData.texTile.x = texTile;
            moduleList1.push_back(shipModuleData);
        }
    }
    shipModuleData.name = "GM01";
    shipModuleData.offset.y = 5;
    moduleList1.push_back(shipModuleData);
    moduleList2.push_back(mdata);
    /**SHIP MODULES**/


    /**SHIP CHUNKS**/
    ChunkData largeChunkData;
    largeChunkData.isBullet = false;
    largeChunkData.isEnabled = true;
    largeChunkData.bodyType = b2BodyType::b2_dynamicBody;
    largeChunkData.type = ClassType::CHUNK;
    ShipData shipDat;
    shipDat.isBullet = false;
    shipDat.isEnabled = true;
    shipDat.bodyType = b2BodyType::b2_dynamicBody;
    shipDat.type = ClassType::SHIP;

    largeChunkData.position = b2Vec2(-5, -5);
    Chunk* chunk0 = new Chunk(largeChunkData);
    chunk0->setName("bigChunk_56");
    chunk0->add(moduleList1, example);
    //chunk0->add(moduleList2);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(chunk0));

    largeChunkData.position = b2Vec2(20, -20);
    Chunk* chunk1 = new Chunk(largeChunkData);
    chunk1->setName("bigChunk_2");
    chunk1->add(moduleList1, example);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(chunk1));

    shipDat.position = b2Vec2(-20, 20);
    Chunk* ship1 = new Ship(shipDat);//WTF IS GOING ON (solved, the force field wasnt getting initialized properly)
    ship1->setName("ship_1");
    ship1->add(moduleList1, example);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(ship1));
    /**SHIP CHUNKS**/

    /**=============================================SHIPS=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**======================DEBRIS============================**/

    /**DEBRIS MODULES**/
    GModuleData debrisModuleData;
    debrisModuleData.type = ClassType::GMODULE;
    debrisModuleData.shape = Shape::Box;
    debrisModuleData.categoryBits = CollisionCategory::Projectile;
    debrisModuleData.maskBits = CollisionCategory::ShipModule | CollisionCategory::Sensor;
    debrisModuleData.isSensor = false;
    debrisModuleData.density = 1.0f;
    debrisModuleData.friction = 0.4f;
    debrisModuleData.halfSize = b2Vec2(0.25, 0.25);
    debrisModuleData.offset = b2Vec2(0, 0);
    debrisModuleData.pBody = NULL;//we dont know it yet
    debrisModuleData.restitution = 0.2f;
    debrisModuleData.rotation = 0.0f;
    debrisModuleData.texName = "textures/door1.png";
    debrisModuleData.texTile = sf::Vector2f(0, 0);
    debrisModuleData.texTileSize = sf::Vector2f(64, 64);
    debrisModuleData.color = sf::Color::White;

    vector<GModuleData> DebrisDataList;
    DebrisDataList.push_back(debrisModuleData);
    DebrisDataList.back().offset.x = 0;
    DebrisDataList.back().offset.y = 0;
    DebrisDataList.back().texTile.x = 0;

    DebrisDataList.push_back(debrisModuleData);
    DebrisDataList.back().texTile.x = 1;
    DebrisDataList.back().offset.x = offsetDelta;
    DebrisDataList.back().offset.y = 0;
    /**DEBRIS MODULES**/


    /**DEBRIS CHUNKS**/
    ChunkData debrisData;
    debrisData.bodyType = b2BodyType::b2_dynamicBody;
    debrisData.position.x = 50;
    debrisData.position.y = -50;
    debrisData.isBullet = false;
    debrisData.type = ClassType::CHUNK;

    Chunk* debrisChunk = new Chunk(debrisData);
    debrisChunk->add(DebrisDataList);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));


    for (int i=0, x=1, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList);
        m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    for (int i=0, x=3, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList);
        m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    for (int i=0, x=5, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList);
        m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    /**DEBRIS CHUNKS**/

    /**======================DEBRIS============================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**===========================PLAYER===========================**/

    PlayerData player1;
    player1.name = "player_1";
    player1.type = ClassType::PLAYER;
    player1.playerMode = "god";
    player1.targetName = "ship_1";

    player1.keyConfig.up = sf::Keyboard::W;
    player1.keyConfig.down = sf::Keyboard::S;
    player1.keyConfig.left = sf::Keyboard::Q;
    player1.keyConfig.right = sf::Keyboard::E;
    player1.keyConfig.rollLeft = sf::Keyboard::A;
    player1.keyConfig.rollRight = sf::Keyboard::D;
    player1.keyConfig.special_1 = sf::Keyboard::R;
    player1.keyConfig.special_2 = sf::Keyboard::F;
    player1.keyConfig.special_3 = sf::Keyboard::C;
    player1.keyConfig.special_4 = sf::Keyboard::X;

    player1.keyConfig.primary = sf::Mouse::Left;
    player1.keyConfig.secondary = sf::Mouse::Right;

    m_spControlManager->add(player1);
    /**===========================PLAYER===========================**/
///==============================================================================
///==============================================================================
///==============================================================================



    /**=================================FINALIZING LOADED STUFF===========================================**/
    /**CONTROLLER TARGETS**/
    m_spControlManager->setupControl();
    /**CONTROLLER TARGETS**/

    /**TARGET ID'S**/
    for(vector<Courier*>::iterator it = m_allCouriers.begin(); it != m_allCouriers.end(); ++it)
    {
        if((*it)->package.getDestination() == Destination::UNIVERSE)
            (*it)->package.setTargetID(   m_spUniverse->getTarget((*it)->package.getTargetName())->getID()   );//set the couriers id data

        else if((*it)->package.getDestination() == Destination::GUI)
            m_spOverlayManager->getEventer();///fix this, it should return a target, not damage, just some func

        else if((*it)->package.getDestination() == Destination::GAME)
            this->getEventer();///fix this, it should return a target, not damage, just some func

        else
            this->getEventer();///wtf do we do we do if all that fails?
    }
    /**TARGET ID'S**/
    /**=================================FINALIZING LOADED STUFF===========================================**/
}
