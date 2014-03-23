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




    int loadedFrameRate = 60;///called that because we are supposed to load that
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
    b2World& rWorld = m_spGameUniverse->getWorld();

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
    float firstTime = 0, secondTime = 0, timeForFrame = 0;

    sf::Event event;
    while (m_spGameWindow->isOpen() && newState != Game::Quit)
    {
        secondTime = clock.getElapsedTime().asSeconds();
        timeForFrame = secondTime - firstTime;
        fps = 1.0/timeForFrame;
        firstTime = clock.getElapsedTime().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            cout << "\nFPS: " << fps;

        /**INPUT/UPDATE**////WE need to somehow also factor in tgui!!!
        m_spGameControlManager->pressedUpdate();
        m_spGameUniverse->physStep(timeForFrame);
        while (m_spGameWindow->pollEvent(event))
        {
            if(m_spGameControlManager->choiceUpdate(event))//if we put this before physstep, the camera lags!
                newState = Game::Quit;
        }
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

    /**STATIC CHUNKS**/
    /**^^^GENERIC EXAMPLE**/
    ChunkData chunkData;
    chunkData.position = b2Vec2(-20,-20);
    chunkData.bodyType = b2BodyType::b2_staticBody;
    chunkData.isBullet = false;
    Chunk* temp = new Chunk(chunkData);
    temp->setName("Static_Chunk_1");


    vector<GModuleData> gModuleList3;
    GModuleData solidFixture;
    solidFixture.baseData.type = ClassType::GMODULE;

    solidFixture.baseData.spCourierList.push_back( tr1::shared_ptr<Courier>(new Courier()) );
    Courier& cor = *solidFixture.baseData.spCourierList.front();
    sf::Packet pack;
    pack << "test";
    cor.condition.reset(HEALTH, "97", 97, '<', true);
    cor.package.reset("Static_Chunk_1", "input_1", pack, 1, Destination::UNIVERSE);
    m_allCouriers.push_back(&cor);

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

    gModuleList3.push_back(solidFixture);

    std::vector<b2Vec2> example;
    temp->add(gModuleList3, example);
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(temp));
    /**^^^GENERIC EXAMPLE**/


    /**DYNAMIC CHUNKS**/
    chunkData.bodyType = b2BodyType::b2_dynamicBody;
    chunkData.position = b2Vec2(-5, -5);
    chunkData.baseData.type = ClassType::SHIP;
    Chunk* chunk = new Chunk(chunkData);
    chunkData.position = b2Vec2(20, -20);
    Chunk* chunk1 = new Chunk(chunkData);

    ShipData shipDat;
    chunkData.position = b2Vec2(-20, 20);
    shipDat.chunk = chunkData;
    Chunk* ship1 = new Ship(shipDat);


    //Chunk chunk(b2Vec2(-5, -5));///help is chunk and module destructor set up?

    chunk->setName("bigChunk_1");
    chunk1->setName("bigChunk_2");
    ship1->setName("ship_1");

    GModuleData data;
    data.baseData.type = ClassType::GMODULE;
    data.physicsData.shape = PhysicsBaseData::Box;
    data.physicsData.isSensor = false;
    data.physicsData.density = 1.0f;
    data.physicsData.friction = 0.4f;
    data.physicsData.halfSize = b2Vec2(0.25, 0.25);
    data.physicsData.offset = b2Vec2(0, 0);
    data.physicsData.pBody = NULL;//we dont know it yet
    data.physicsData.restitution = 0.2f;
    data.physicsData.rotation = 0.0f;
    data.graphicsData.texName = "textures/tileset.png";
    data.graphicsData.texTile = sf::Vector2f(0, 0);
    data.graphicsData.texTileSize = sf::Vector2f(64, 64);
    data.graphicsData.color = sf::Color::White;

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
    float offsetDelta = 2*data.physicsData.halfSize.x;
    for (float i=0, x=-2, numBoxsX = 9; i<numBoxsX; ++i, x+=offsetDelta)//creates boxes in a line
    {
        for (float c=0, y=-4.5, numBoxsY = 19; c<numBoxsY; ++c, y+=offsetDelta, ++texTile)
        {
            if (texTile == 4)
                texTile = 0;
            data.physicsData.offset.x = x;
            data.physicsData.offset.y = y;
            data.graphicsData.texTile.x = texTile;
            moduleList1.push_back(data);
        }
    }
    data.baseData.name = "GM01";
    data.physicsData.offset.y = 5;
    moduleList1.push_back(data);
    moduleList2.push_back(mdata);
    //chunk->add(moduleList2);
    chunk->add(moduleList1, example);
    chunk1->add(moduleList1, example);


    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(chunk1));
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(chunk));








    vector<GModuleData> dataList;
    dataList.push_back(data);
    dataList.back().physicsData.offset.x = 0;
    dataList.back().physicsData.offset.y = 0;
    dataList.back().graphicsData.texTile.x = 0;

    dataList.push_back(data);
    dataList.back().graphicsData.texTile.x = 1;
    dataList.back().physicsData.offset.x = offsetDelta;
    dataList.back().physicsData.offset.y = 0;


    chunkData.position.x = 50;
    chunkData.position.y = -50;
    chunkData.isBullet = false;
    chunkData.baseData.type = ClassType::CHUNK;
    temp = new Chunk(chunkData);
    temp->add(dataList);
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(temp));



    chunkData.isBullet = false;

    for (int i=0, x=1, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        chunkData.position.x = x;
        chunkData.position.y = y;
        temp = new Chunk(chunkData);
        temp->add(dataList);
        m_spGameUniverse->add(tr1::shared_ptr<Chunk>(temp));
    }

    for (int i=0, x=3, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        chunkData.position.x = x;
        chunkData.position.y = y;
        temp = new Chunk(chunkData);
        temp->add(dataList);
        m_spGameUniverse->add(tr1::shared_ptr<Chunk>(temp));
    }
    for (int i=0, x=5, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        chunkData.position.x = x;
        chunkData.position.y = y;
        temp = new Chunk(chunkData);
        temp->add(dataList);
        m_spGameUniverse->add(tr1::shared_ptr<Chunk>(temp));
    }



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


        ship1->add(moduleList1);
    m_spGameUniverse->add(tr1::shared_ptr<Chunk>(ship1));


    /**FINALIZING LOADED STUFF**/
    /**LOOP THROUGH CONTROLERS AND SET THEIR TARGETSs**/
    m_spGameControlManager->setupControl();


    /**SET UP TARGET ID's**/


    for(vector<Courier*>::iterator it = m_allCouriers.begin(); it != m_allCouriers.end(); ++it)
    {
        if((*it)->package.getDestination() == Destination::UNIVERSE)
            (*it)->package.setTargetID(   m_spGameUniverse->getTarget((*it)->package.getTargetName())->getID()   );//set the couriers id data

        else if((*it)->package.getDestination() == Destination::GUI)
            m_spGameOverlayManager->damage(0);///fix this, it should return a target, not damage, just some func

        else if((*it)->package.getDestination() == Destination::GAME)
            this->damage(0);///fix this, it should return a target, not damage, just some func

        else
            this->damage(0);///wtf do we do we do if all that fails?
    }
}
