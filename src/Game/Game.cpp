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
    m_spGameWindow = std::tr1::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1200, 600), "SFML Box2D Test Environment", sf::Style::Default, m_settings));
    m_spGameFunctionFinder = std::tr1::shared_ptr<BaseFunctionFinder>(new BaseFunctionFinder);//independent
    m_spTexAlloc = std::tr1::shared_ptr<TextureAllocator>(new TextureAllocator());//independent
    m_spGameOverlayManager = std::tr1::shared_ptr<OverlayManager>(new OverlayManager());//independent
    m_spGameUniverse = std::tr1::shared_ptr<Universe>(new Universe());//independent
    /**created last**/
    m_spGameControlManager = std::tr1::shared_ptr<ControlManager>(new ControlManager);//needs Window and Universe
    m_spGameIOManager = std::tr1::shared_ptr<IOManager>(new IOManager(*this));//requires Universe and OverlayManager



    bool vsinc = true;
    int loadedFrameRate = 60;///called that because we are supposed to load that
    m_spGameWindow->setVerticalSyncEnabled(vsinc);
    m_spGameWindow->setFramerateLimit(loadedFrameRate);
    m_spGameFunctionFinder->load("functionTable.tbl");
    ///This code won't work! WTF?
    ///if(!icon.loadFromFile("textures/tileset.png"))
    /// cout << "\nIcon Load Error";///texture allocator
    ///m_gameWindow.setIcon(32, 32, icon.getPixelsPtr());
}
Game::~Game()//unfinished
{

}
IOManager& Game::getGameIOManager()
{
    return *m_spGameIOManager;
}
sf::RenderWindow& Game::getGameWindow()
{
    return *m_spGameWindow;
}
TextureAllocator& Game::getTextureAllocator()
{
    return *m_spTexAlloc;
}
Universe& Game::getGameUniverse()
{
    return *m_spGameUniverse;
}
OverlayManager& Game::getGameOverlayManager()
{
    return *m_spGameOverlayManager;
}
BaseFunctionFinder& Game::getGameFunctionFinder()
{
    return *m_spGameFunctionFinder;
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
    /**initialize**/
 //   b2World& rWorld = m_spGameUniverse->getWorld();

    f_load("stuff");
    /**HUD**/
    sf::ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0, sf::Vector2f(0, 0));
    convex.setPoint(1, sf::Vector2f(150, 10));
    convex.setPoint(2, sf::Vector2f(60, 30));
    convex.setPoint(3, sf::Vector2f(30, 100));
    convex.setPoint(4, sf::Vector2f(0, 50));


    /**SIMULATION & RUNTIME**/
    Game::Status newState = Game::Local;
    sf::Clock clock;
    float fps = 0;
    float firstTime = 0, secondTime = 0, timeForFrame = 0, computeTime = 0, remainder = 0;
    int i = 0;

    sf::Event event;
    while (m_spGameWindow->isOpen() && newState != Game::Quit)
    {
        secondTime = clock.getElapsedTime().asSeconds();
        timeForFrame = secondTime - firstTime;
        computeTime = timeForFrame + remainder;
        fps = 1.0/timeForFrame;
        firstTime = clock.getElapsedTime().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            cout << "\nFPS: " << fps;

        /**INPUT and PHYSICS**/



        while (m_spGameWindow->pollEvent(event))
        {
            if(m_spGameControlManager->choiceUpdate(event))//if we put this before physstep, the camera lags!
                newState = Game::Quit;
        }

        while(computeTime > 0 && i < 6)///should max iterations depend on how far we are behind?
        {
            ++i;
            m_spGameControlManager->pressedUpdate();
            computeTime -= m_spGameUniverse->physStep();
        }
        remainder = computeTime;
        i = 0;
        if(remainder > 0)
            cout << endl << remainder;


        m_spGameIOManager->update(timeForFrame);



        /**DRAW**/
        m_spGameWindow->clear();
        m_spGameControlManager->drawUpdate();

        m_spGameWindow->setView(m_spGameWindow->getDefaultView());//draw stuff that is on hud
        convex.setPosition(m_spGameWindow->mapPixelToCoords(sf::Vector2i(40,40)));
        m_spGameWindow->draw(convex);

        m_spGameWindow->display();
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
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================STATIC=============================================**/

    /**STATIC CHUNK**/
    ChunkData staticChunkData;
    staticChunkData.position = b2Vec2(-20,-20);
    staticChunkData.bodyType = b2BodyType::b2_staticBody;
    staticChunkData.isBullet = false;
    Chunk* staticChunk = new Chunk(staticChunkData);
    staticChunk->setName("Static_Chunk_1");

    vector<GModuleData> staticGModuleDataList;
    /**STATIC CHUNK**/

    /**STATIC MODULES**/
    GModuleData solidFixture;
    solidFixture.baseData.type = ClassType::GMODULE;

    solidFixture.baseData.spCourierList.push_back( tr1::shared_ptr<Courier>(new Courier()) );
    Courier& cor = *solidFixture.baseData.spCourierList.front();
    sf::Packet pack;
    pack << "test";
    cor.condition.reset(HEALTH, "97", 97, '<', true);
    cor.package.reset("Static_Chunk_1", "input_1", pack, 1, Destination::UNIVERSE);
    m_allCouriers.push_back(&cor);

    solidFixture.physicsData.isSensor = false;
    solidFixture.physicsData.shape = PhysicsBaseData::Octagon;
    solidFixture.physicsData.density = 1.0f;
    solidFixture.physicsData.friction = 0.4f;
    solidFixture.physicsData.halfSize = b2Vec2(2, 5);
    solidFixture.physicsData.offset = b2Vec2(0, 0);
    solidFixture.physicsData.pBody = NULL;//we dont know it yet
    solidFixture.physicsData.restitution = 0.2f;
    solidFixture.physicsData.rotation = 0.0f;
    solidFixture.graphicsData.texName = "textures/tileset.png";
    solidFixture.graphicsData.texTile = sf::Vector2f(0, 0);
    solidFixture.graphicsData.texTileSize = sf::Vector2f(64, 64);
    solidFixture.graphicsData.color = sf::Color::Red;

    staticGModuleDataList.push_back(solidFixture);

    std::vector<b2Vec2> example;
    staticChunk->add(staticGModuleDataList, example);
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(staticChunk));
    /**STATIC MODULES**/

    /**=============================================STATIC=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================SHIPS=============================================**/

    /**LARGE DYNAMIC CHUNKS**/
    ChunkData largeChunkData;
    largeChunkData.isBullet = false;
    largeChunkData.bodyType = b2BodyType::b2_dynamicBody;
    largeChunkData.baseData.type = ClassType::CHUNK;

    largeChunkData.position = b2Vec2(-5, -5);
    Chunk* chunk0 = new Chunk(largeChunkData);


    largeChunkData.position = b2Vec2(20, -20);
    Chunk* chunk1 = new Chunk(largeChunkData);

    ShipData shipDat;
    shipDat.chunk.isBullet = false;
    shipDat.chunk.baseData.isEnabled = true;
    shipDat.chunk.bodyType = b2BodyType::b2_dynamicBody;
    shipDat.chunk.baseData.type = ClassType::SHIP;

    shipDat.chunk.position = b2Vec2(-20, 20);
    Chunk* ship1 = new Ship(shipDat);    ///WTF IS GOING ON


    chunk0->setName("bigChunk_56");///if we put this before new ship()the ship is broken
    chunk1->setName("bigChunk_2");
    ship1->setName("ship_1");


    GModuleData shipModuleData;
    shipModuleData.baseData.type = ClassType::GMODULE;
    shipModuleData.physicsData.shape = PhysicsBaseData::Box;
    shipModuleData.physicsData.categoryBits = CollisionCategory::ShipModule;
    shipModuleData.physicsData.maskBits = CollisionCategory::Projectile;
    shipModuleData.physicsData.isSensor = false;
    shipModuleData.physicsData.density = 1.0f;
    shipModuleData.physicsData.friction = 0.4f;
    shipModuleData.physicsData.halfSize = b2Vec2(0.25, 0.25);
    shipModuleData.physicsData.offset = b2Vec2(0, 0);
    shipModuleData.physicsData.pBody = NULL;//we dont know it yet
    shipModuleData.physicsData.restitution = 0.2f;
    shipModuleData.physicsData.rotation = 0.0f;
    shipModuleData.graphicsData.texName = "textures/tileset.png";
    shipModuleData.graphicsData.texTile = sf::Vector2f(0, 0);
    shipModuleData.graphicsData.texTileSize = sf::Vector2f(64, 64);
    shipModuleData.graphicsData.color = sf::Color::White;

    ModuleData mdata;
    mdata.baseData.type = ClassType::MODULE;
    mdata.physicsData.density = 1.0f;
    mdata.physicsData.friction = 0.4f;
    mdata.physicsData.halfSize = b2Vec2(0.25, 0.25);
    mdata.physicsData.offset = b2Vec2(0, -5);
    mdata.physicsData.pBody = NULL;//we dont know it yet
    mdata.physicsData.restitution = 0.2f;
    mdata.physicsData.rotation = 0.0f;

    ///WE NEED TO GET A STANDARD SIZE
    vector<GModuleData> moduleList1;
    vector<ModuleData> moduleList2;
    short int texTile = 0;
    float offsetDelta = 2*shipModuleData.physicsData.halfSize.x;
    for (float i=0, x=-2, numBoxsX = 9; i<numBoxsX; ++i, x+=offsetDelta)//creates boxes in a line
    {
        for (float c=0, y=-4.5, numBoxsY = 19; c<numBoxsY; ++c, y+=offsetDelta, ++texTile)
        {
            if (texTile == 4)
                texTile = 0;
            shipModuleData.physicsData.offset.x = x;
            shipModuleData.physicsData.offset.y = y;
            shipModuleData.graphicsData.texTile.x = texTile;
            moduleList1.push_back(shipModuleData);
        }
    }
    shipModuleData.baseData.name = "GM01";
    shipModuleData.physicsData.offset.y = 5;
    moduleList1.push_back(shipModuleData);
    moduleList2.push_back(mdata);
    //chunk0->add(moduleList2);
    chunk0->add(moduleList1, example);
    chunk1->add(moduleList1, example);


    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(chunk1));
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(chunk0));

    /**LARGE DYNAMIC CHUNKS**/

    /**=============================================SHIPS=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
/**======================DEBRIS============================**/

    /**DEBRIS MODULES**/
    GModuleData debrisModuleData;
    debrisModuleData.baseData.type = ClassType::GMODULE;
    debrisModuleData.physicsData.shape = PhysicsBaseData::Box;
    debrisModuleData.physicsData.categoryBits = CollisionCategory::Projectile;
    debrisModuleData.physicsData.maskBits = CollisionCategory::ShipModule | CollisionCategory::Sensor;
    debrisModuleData.physicsData.isSensor = false;
    debrisModuleData.physicsData.density = 1.0f;
    debrisModuleData.physicsData.friction = 0.4f;
    debrisModuleData.physicsData.halfSize = b2Vec2(0.25, 0.25);
    debrisModuleData.physicsData.offset = b2Vec2(0, 0);
    debrisModuleData.physicsData.pBody = NULL;//we dont know it yet
    debrisModuleData.physicsData.restitution = 0.2f;
    debrisModuleData.physicsData.rotation = 0.0f;
    debrisModuleData.graphicsData.texName = "textures/tileset.png";
    debrisModuleData.graphicsData.texTile = sf::Vector2f(0, 0);
    debrisModuleData.graphicsData.texTileSize = sf::Vector2f(64, 64);
    debrisModuleData.graphicsData.color = sf::Color::White;

    debrisModuleData.physicsData.categoryBits = CollisionCategory::Projectile;
    debrisModuleData.physicsData.maskBits = CollisionCategory::ShipModule | CollisionCategory::Sensor;
    vector<GModuleData> DebrisDataList;
    DebrisDataList.push_back(debrisModuleData);
    DebrisDataList.back().physicsData.offset.x = 0;
    DebrisDataList.back().physicsData.offset.y = 0;
    DebrisDataList.back().graphicsData.texTile.x = 0;

    DebrisDataList.push_back(debrisModuleData);
    DebrisDataList.back().graphicsData.texTile.x = 1;
    DebrisDataList.back().physicsData.offset.x = offsetDelta;
    DebrisDataList.back().physicsData.offset.y = 0;
    /**DEBRIS MODULES**/


    /**DEBRIS CHUNKS**/
    ChunkData debrisData;
    debrisData.bodyType = b2BodyType::b2_dynamicBody;
    debrisData.position.x = 50;
    debrisData.position.y = -50;
    debrisData.isBullet = false;
    debrisData.baseData.type = ClassType::CHUNK;
    Chunk* debrisChunk = new Chunk(debrisData);
    debrisChunk->add(DebrisDataList);
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    for (int i=0, x=1, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList);
        m_spGameUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    for (int i=0, x=3, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList);
        m_spGameUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    for (int i=0, x=5, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList);
        m_spGameUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    /**DEBRIS CHUNKS**/


/**======================DEBRIS============================**/
///==============================================================================
///==============================================================================
///==============================================================================
/**===========================PLAYER===========================**/
    PlayerData player1;
    player1.intellData.baseData.name = "player_1";
    player1.intellData.baseData.type = ClassType::PLAYER;
    player1.playerMode = "god";
    player1.intellData.targetName = "ship_1";

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

    m_spGameControlManager->add(player1);
/**===========================PLAYER===========================**/
///==============================================================================
///==============================================================================
///==============================================================================


    ship1->add(moduleList1);///WTF
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(ship1));///WTF

    /**=================================FINALIZING LOADED STUFF===========================================**/
    /**CONTROLLER TARGETS**/
    m_spGameControlManager->setupControl();
    /**CONTROLLER TARGETS**/

    /**TARGET ID'S**/
    for(vector<Courier*>::iterator it = m_allCouriers.begin(); it != m_allCouriers.end(); ++it)
    {
        if((*it)->package.getDestination() == Destination::UNIVERSE)
            (*it)->package.setTargetID(   m_spGameUniverse->getTarget((*it)->package.getTargetName())->getID()   );//set the couriers id data

        else if((*it)->package.getDestination() == Destination::GUI)
            m_spGameOverlayManager->getEventer();///fix this, it should return a target, not damage, just some func

        else if((*it)->package.getDestination() == Destination::GAME)
            this->getEventer();///fix this, it should return a target, not damage, just some func

        else
            this->getEventer();///wtf do we do we do if all that fails?
    }
    /**TARGET ID'S**/
    /**=================================FINALIZING LOADED STUFF===========================================**/
}
