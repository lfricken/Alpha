/**WONT BE NEEDED**/
#include "Chunk.h"
#include "Ship.h"

#include "GModule.h"
#include "Module.h"
#include "Button.h"
/**WONT BE NEEDED**/

#include "Sort.h"
#include "Game.h"
#include "globals.h"
#include "IOManager.h"
#include "ControlManager.h"
#include "BaseFunctionFinder.h"

#include "Armor.h"
#include "ForceFieldCore.h"
#include "AnimationLooper.h"

using namespace std;

Game::Game()
{
    ///load window data into settings, and launch window with the settings
    m_settings.antialiasingLevel = 4;

    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    mode = sf::VideoMode(1200, 700, 32);
    m_spWindow = std::tr1::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(mode, "SFML Box2D Test Environment", sf::Style::Default, m_settings));
    m_spFunctionFinder = std::tr1::shared_ptr<BaseFunctionFinder>(new BaseFunctionFinder);//independent
    m_spTexAlloc = std::tr1::shared_ptr<TextureAllocator>(new TextureAllocator());//independent
    m_spUniverse = std::tr1::shared_ptr<Universe>(new Universe());//independent
    /**created last**/
    m_spOverlayManager = std::tr1::shared_ptr<OverlayManager>(new OverlayManager(*m_spWindow));//independent
    m_spIOManager = std::tr1::shared_ptr<IOManager>(new IOManager(*this));//requires Universe and OverlayManager
    m_spControlManager = std::tr1::shared_ptr<ControlManager>(new ControlManager);//needs Window and Universe and GUI

    m_spUniverse->resetEventer();/**these objects need to create an IOBase, and thus need an active eventer, and thus need a pointer to IOManager**/
    m_spOverlayManager->resetEventer();/** ^ **/
    this->resetEventer();/** ^ **/

    bool loadedVsinc = true;
    int loadedFrameRate = 60;///called that because we are supposed to load that info
    std::string loadedFont = "TGUI/fonts/DejaVuSans.ttf";

    m_spOverlayManager->getGui().setGlobalFont(loadedFont);
    m_spWindow->setVerticalSyncEnabled(loadedVsinc);
    m_spWindow->setFramerateLimit(loadedFrameRate);
    m_spFunctionFinder->load("functionTable.tbl");
    ///This code won't work! WTF?
    ///if(!icon.loadFromFile("textures/tileset.png"))
    /// cout << "\nIcon Load Error";///texture allocator
    ///m_spWindow.setIcon(32, 32, icon.getPixelsPtr());

///FIGURE OUT HOW TO USE POST EFFECTS
    /**
        if (sf::Shader::isAvailable())
            cout << "\nCan use post effects.";
        else
            cout << "\nCan NOT use post effects.";

        sf::Shader effect;
        string effectName = "colorize.sfx";
        if (!effect.loadFromFile(effectName, sf::Shader::Fragment))
            cout << "\nFailed to load [" << effectName << "].";
        else
            cout << "\nLoaded [" << effectName << "].";**/

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
    /**LOAD THE GAME**/
    f_load("stuff");
    /**SIMULATION & RUNTIME**/
    Game::Status newState = Game::Local;

    float fps = 0;
    float firstTime = 0, secondTime = 0, timeForFrame = 0, computeTime = 0, remainder = 0;
    int i = 0;

    int gray = 60;

    sf::Event event;
    while(m_spWindow->isOpen() && newState != Game::Quit)
    {
        secondTime = getTime();
        timeForFrame = secondTime - firstTime;
        computeTime = timeForFrame + remainder;
        fps = 1.0/timeForFrame;
        firstTime = getTime();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            if(fps < 35.0f)
                cout << "\n\tFPS: " << fps;
            else
                cout << "\nFPS: " << fps;
        }
        /**INPUT and PHYSICS**/
        while(m_spWindow->pollEvent(event))
        {
            if(m_spControlManager->choiceUpdate(event))//if we put this before physstep, the camera lags!
                newState = Game::Quit;
        }
        for(i = 0; computeTime > 0 && i < 6; ++i)///should max iterations depend on how far we are behind?
        {
            m_spControlManager->pressedUpdate();
            computeTime -= m_spUniverse->physStep();
        }
        remainder = computeTime;

        if(remainder > 0)
            cout << endl << remainder;

        m_spIOManager->update(timeForFrame);
        /**INPUT and PHYSICS**/



        /**DRAW**/

        m_spWindow->clear(sf::Color(gray,gray,gray,255));
        m_spControlManager->drawUpdate();
        m_spOverlayManager->draw();
        //m_spWindow->setView(m_spWindow->getDefaultView());///draw stuff that is on hud///this doesn't appear to do anything anymore

        m_spWindow->display();
        /**DRAW**/
    }
    return newState;
}
float Game::getTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}
void Game::f_load(const std::string& stuff)///ITS NOT CLEAR WHAT WE ARE LOADING EXACTLY, defaults states?, maps?, screen items?
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
    tgui::Tab::Ptr tab(m_spOverlayManager->getGui());///TEMPORARY, JUST FOR TESTS, NEED TO MAKE MY OWN CONTAINER FOR THIS
    tab->load(config);
    tab->setPosition(300, 10);
    tab->add("Weapon");
    tab->add("Ammo");
    tab->add("Items");

    leon::PanelData panelData;
    panelData.configFile = config;
    panelData.backgroundColor = sf::Color(255,255,255,1);
    panelData.position = sf::Vector2f(0, 0);
    panelData.size = sf::Vector2f(200,200);
    panelData.type = ClassType::PANEL;

    tr1::shared_ptr<leon::Panel> panel(new leon::Panel(m_spOverlayManager->getGui(), panelData));
    m_spOverlayManager->add(panel);

    leon::ButtonData buttonData;
    buttonData.size = sf::Vector2f(100,50);
    buttonData.buttonText = "Exit";
    buttonData.position = sf::Vector2f(0, 0);
    buttonData.type = ClassType::BUTTON;

    Courier* pCourier = new Courier();
    sf::Packet pack;
    pack << "packet data";
    pCourier->condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    pCourier->package.reset("Static_Chunk_1", "input_1", pack, 0, Destination::UNIVERSE);

    buttonData.spCourierList.push_back(tr1::shared_ptr<Courier>(pCourier));
    tr1::shared_ptr<leon::WidgetBase> button(new leon::Button(*(panel->getPanel()), buttonData));
    panel->add(button);



    /**TAB**/

    /**
        leon::ButtonData buttonData;
        buttonData.size = sf::Vector2f(100,50);
        buttonData.buttonText = "Win";
        buttonData.position = sf::Vector2f(20, 300);

        leon::Button(*m_spGui, buttonData);///we need this button to be deleted so its temporarily in the main loop
        **/


    /**=============================================GUI=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================STATIC=============================================**/

    std::vector<b2Vec2> example;

    /**STATIC MODULES**/
    vector<tr1::shared_ptr<GModuleData> > staticGModuleDataList;
    GModuleData solidFixtureData;
    solidFixtureData.type = ClassType::GMODULE;

    solidFixtureData.spCourierList.push_back( tr1::shared_ptr<Courier>(new Courier()) );
    Courier& cor = *solidFixtureData.spCourierList.front();
    sf::Packet packet;
    packet << "testData";
    cor.condition.reset(Event::Health, "97", 97, '<', true);
    cor.package.reset("Static_Chunk_1", "input_1", packet, 1, Destination::UNIVERSE);

    solidFixtureData.isSensor = false;
    solidFixtureData.shape = Shape::OCTAGON;
    solidFixtureData.density = 1.0f;
    solidFixtureData.friction = 0.4f;
    solidFixtureData.halfSize = b2Vec2(2, 5);
    solidFixtureData.offset = b2Vec2(0, 0);
    solidFixtureData.pBody = NULL;//we dont know it yet
    solidFixtureData.restitution = 0.2f;
    // solidFixtureData.rotation = 0.0f;
    solidFixtureData.texName = "textures/default.png";
    solidFixtureData.texTile = sf::Vector2f(0, 0);
    solidFixtureData.color = sf::Color::Red;

    staticGModuleDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(solidFixtureData)));
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
    Courier* pModuleCourier = new Courier();
    sf::Packet modPack;
    modPack << "eventing works!";
    pModuleCourier->condition.reset(Event::Health, "50", 50, '<', true);
    pModuleCourier->package.reset("Static_Chunk_1", "input_1", modPack, 0, Destination::UNIVERSE);

    GModuleData shipModuleData;
    shipModuleData.spCourierList.push_back(tr1::shared_ptr<Courier>(pModuleCourier));

    shipModuleData.type = ClassType::GMODULE;
    shipModuleData.shape = Shape::BOX;
    shipModuleData.categoryBits = Category::ShipModule;
    shipModuleData.maskBits = MaskBits::ShipModuleNorm;
    shipModuleData.isSensor = false;
    shipModuleData.density = 1.0f;
    shipModuleData.friction = 0.4f;
    shipModuleData.halfSize = b2Vec2(0.25, 0.25);
    shipModuleData.offset = b2Vec2(0, 0);
    shipModuleData.pBody = NULL;//we dont know it yet
    shipModuleData.restitution = 0.2f;
    //  shipModuleData.rotation = 0.0f;
    shipModuleData.texName = "textures/default.png";
    shipModuleData.texTile = sf::Vector2f(0, 0);
    shipModuleData.color = sf::Color::White;

    ModuleData mdata;
    mdata.type = ClassType::MODULE;
    mdata.shape = Shape::TRIANGLE;
    mdata.rotation = 0.0f;
    mdata.categoryBits = Category::ShipModule;
    mdata.maskBits = MaskBits::ShipModuleNorm;
    mdata.density = 1.0f;
    mdata.friction = 0.4f;
    mdata.halfSize = b2Vec2(0.25, 0.25);
    mdata.offset = b2Vec2(0, -5);
    mdata.pBody = NULL;//we dont know it yet
    mdata.restitution = 0.2f;

    ModuleData hull;
    hull.type = ClassType::HULL;
    hull.shape = Shape::POLYGON;
    hull.vertices.push_back(b2Vec2(3, 5));
    hull.vertices.push_back(b2Vec2(-3, 5));
    hull.vertices.push_back(b2Vec2(-3, -5));
    hull.vertices.push_back(b2Vec2(0, -6));
    hull.vertices.push_back(b2Vec2(3, -5));

    hull.rotation = 0.0f;
    hull.categoryBits = Category::ShipHull;
    hull.maskBits = MaskBits::ShipHull;
    hull.density = 0.0f;
    hull.friction = 0.4f;
    hull.halfSize = b2Vec2(4, 4);
    hull.offset = b2Vec2(0, 0);
    hull.pBody = NULL;//we dont know it yet
    hull.restitution = 0.2f;
    hull.butes.setBute(Butes::isDestructable, false);
    hull.butes.setBute(Butes::isSolid, true);

    ///WE NEED TO GET A STANDARD SIZE??
    vector<tr1::shared_ptr<GModuleData> > moduleList1;
    vector<tr1::shared_ptr<ModuleData> > moduleList2;
    short int texTile = 0;
    float offsetDelta = 2*shipModuleData.halfSize.x;
    for (float i=0, x=-1.5, numBoxsX = 7; i<numBoxsX; ++i, x+=offsetDelta)//creates boxes in a line
    {
        for (float c=0, y=-4.0, numBoxsY = 17; c<numBoxsY; ++c, y+=offsetDelta)
        {
            if((x!=0) || (y!=0))
            {
                shipModuleData.offset.x = x;
                shipModuleData.offset.y = y;
                //shipModuleData.texTile.x = texTile;
                moduleList1.push_back( tr1::shared_ptr<GModuleData>(new GModuleData(shipModuleData)) );
            }
        }
    }

    ArmorData armorData;
    //armorData.spCourierList.push_back(tr1::shared_ptr<Courier>(pModuleCourier));

    armorData.type = ClassType::GMODULE;
    armorData.shape = Shape::BOX;
    armorData.categoryBits = Category::ShipModule;
    armorData.maskBits = MaskBits::ShipModuleNorm;
    armorData.isSensor = false;
    armorData.density = 1.0f;
    armorData.friction = 0.4f;
    armorData.halfSize = b2Vec2(0.25, 0.25);
    armorData.offset = b2Vec2(0, 0);
    armorData.pBody = NULL;//we dont know it yet
    armorData.restitution = 0.2f;

    armorData.texName = "textures/armor/armor.png";
    armorData.texTile = sf::Vector2f(3, 0);
    armorData.color = sf::Color::White;
    for (float i=0, x=-4, y=-9, numBoxsX = 19; i<numBoxsX; ++i, ++y)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ArmorData(armorData)) );
    }
    for (float i=0, x=4, y=-9, numBoxsX = 19; i<numBoxsX; ++i, ++y)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ArmorData(armorData)) );
    }
    for (float i=0, x=-2, y=-9, numBoxsX = 5; i<numBoxsX; ++i, ++x)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ArmorData(armorData)) );
    }
    for (float i=0, x=-2, y=9, numBoxsX = 5; i<numBoxsX; ++i, ++x)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ArmorData(armorData)) );
    }

    ForceFieldCoreData fieldCoreData;
    //armorData.spCourierList.push_back(tr1::shared_ptr<Courier>(pModuleCourier));

    fieldCoreData.type = ClassType::FORCE;
    fieldCoreData.shape = Shape::BOX;
    fieldCoreData.categoryBits = Category::ShipModule;
    fieldCoreData.maskBits = MaskBits::ShipModuleNorm;
    fieldCoreData.isSensor = false;
    fieldCoreData.density = 1.0f;
    fieldCoreData.friction = 0.4f;
    fieldCoreData.halfSize = b2Vec2(0.25, 0.25);
    fieldCoreData.offset = b2Vec2(0, 0);
    fieldCoreData.pBody = NULL;//we dont know it yet
    fieldCoreData.restitution = 0.2f;
    //fieldCoreData.rotation = 0.0f;
    fieldCoreData.texName = "textures/default.png";
    fieldCoreData.texTile = sf::Vector2f(1, 0);
    fieldCoreData.color = sf::Color::White;
    moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ForceFieldCoreData(fieldCoreData)) );


    shipModuleData.rotation = 90;
    shipModuleData.shape = Shape::TRIANGLE;
    shipModuleData.name = "GM01";
    shipModuleData.offset.y = 5;
    moduleList1.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(shipModuleData)));
    moduleList2.push_back(tr1::shared_ptr<ModuleData>(new ModuleData(mdata)));
    moduleList2.push_back(tr1::shared_ptr<ModuleData>(new ModuleData(hull)));
    ///SortPtrVector(moduleList1, &IOBaseData::getID);

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

    shipDat.position = b2Vec2(-5, -5);
    Chunk* chunk0 = new Ship(shipDat);
    chunk0->setName("bigChunk_56");
    chunk0->add(moduleList1, example);
    chunk0->add(moduleList2);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(chunk0));

    shipDat.position = b2Vec2(20, -20);
    Chunk* chunk1 = new Ship(shipDat);
    chunk1->setName("bigChunk_2");
    chunk1->add(moduleList1, example);
    chunk1->add(moduleList2);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(chunk1));

    shipDat.position = b2Vec2(-20, 20);
    Chunk* ship1 = new Ship(shipDat);
    ship1->setName("ship_1");
    ship1->add(moduleList1, example);
    ship1->add(moduleList2);
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
    debrisModuleData.shape = Shape::BOX;
    debrisModuleData.categoryBits = Category::Projectile;
    debrisModuleData.maskBits = MaskBits::ProjectileNorm;
    debrisModuleData.isSensor = false;
    debrisModuleData.density = 1.0f;
    debrisModuleData.friction = 0.4f;
    debrisModuleData.halfSize = b2Vec2(0.25, 0.25);
    debrisModuleData.offset = b2Vec2(0, 0);
    debrisModuleData.pBody = NULL;//we dont know it yet
    debrisModuleData.restitution = 0.2f;
    debrisModuleData.rotation = 0.0f;
    debrisModuleData.texTile = sf::Vector2f(0, 0);
    debrisModuleData.color = sf::Color::White;

    vector<tr1::shared_ptr<GModuleData> > DebrisDataList;
    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));//copy constructor
    DebrisDataList.back()->offset.x = 0;
    DebrisDataList.back()->offset.y = 0;
    DebrisDataList.back()->texTile.x = 0;

    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));
    DebrisDataList.back()->texTile.x = 1;
    DebrisDataList.back()->offset.x = offsetDelta;
    DebrisDataList.back()->offset.y = 0;
    /**DEBRIS MODULES**/


    /**DEBRIS CHUNKS**/
    ChunkData debrisData;
    debrisData.bodyType = b2BodyType::b2_dynamicBody;
    debrisData.position.x = 50;
    debrisData.position.y = -50;
    debrisData.isBullet = true;
    debrisData.type = ClassType::CHUNK;

    Chunk* debrisChunk = new Chunk(debrisData);
    debrisChunk->add(DebrisDataList, example);
    m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));

    DebrisDataList.back()->texName = "textures/door_1.png";
    DebrisDataList.front()->texName = "textures/door_1.png";

    for (int i=0, x=1, y=3, numBoxs = 100; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList, example);
        m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    for (int i=0, x=3, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList, example);
        m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    for (int i=0, x=5, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        debrisChunk = new Chunk(debrisData);
        debrisChunk->add(DebrisDataList, example);
        m_spUniverse->add(tr1::shared_ptr<Chunk>(debrisChunk));
    }
    /**DEBRIS CHUNKS**/

    /**======================DEBRIS============================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**===========================PLAYER===========================**/

    /**PLAYER**/
    PlayerData player1;
    player1.name = "player_1";
    player1.type = ClassType::PLAYER;
    player1.playerMode = PlayerMode::God;
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

    player1.cameraPos = sf::Vector2f(0, 0);
    player1.cameraSize = (static_cast<sf::Vector2f>(m_spWindow->getSize()));

    tr1::shared_ptr<Player> spPlayer(new Player(player1));
    m_spControlManager->add(spPlayer);
    /**PLAYER**/

    /**===========================PLAYER===========================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=================================FINALIZING LOADED STUFF===========================================**/

    /**CONTROLLER TARGETS**/
    m_spControlManager->setupControl();
    /**CONTROLLER TARGETS**/

    /**=================================FINALIZING LOADED STUFF===========================================**/
}
