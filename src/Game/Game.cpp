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

#include "Armor.h"
#include "ForceFieldCore.h"
#include "Thruster.h"

#include "EditBox.h"

//#include "AnimationLooper.h"

#include "Decoration.h"

using namespace std;

Game::Game()
{
    ///load window data into settings, and launch window with the settings
    m_settings.antialiasingLevel = 4;

    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    mode = sf::VideoMode(1200, 800, 32);
    //mode =
    m_spWindow = std::tr1::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(mode, "SFML Box2D Test Environment", sf::Style::Default, m_settings));

    m_spIOManager = std::tr1::shared_ptr<IOManager>(new IOManager());//independent
    m_spTexAlloc = std::tr1::shared_ptr<TextureAllocator>(new TextureAllocator());//independent
    m_spUniverse = std::tr1::shared_ptr<Universe>(new Universe());//independent

    /**created last**/
    m_spOverlayManager = std::tr1::shared_ptr<OverlayManager>(new OverlayManager(*m_spWindow));//needs Window
    m_spControlManager = std::tr1::shared_ptr<ControlManager>(new ControlManager());//needs Window and Universe and GUI



    bool loadedVsinc = false;
    int loadedFrameRate = 60;///called that because we are supposed to load that info
    std::string loadedFont = "TGUI/fonts/DejaVuSans.ttf";

    m_spOverlayManager->getGui().setGlobalFont(loadedFont);
    m_spWindow->setVerticalSyncEnabled(loadedVsinc);
    m_spWindow->setFramerateLimit(loadedFrameRate);
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
    /**SIMULATION & RUNTIME**/

    sf::Event event;
    while(m_spWindow->isOpen() && newState != Game::Quit)
    {
        /**FPS**/
        secondTime = getTime();
        timeForFrame = secondTime - firstTime;
        computeTime = timeForFrame + remainder;
        fps = 1.0/timeForFrame;
        firstTime = getTime();

        if(fps < 40)
            cout << "\nFPS: " << fps;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            if(fps < 35.0f)
                cout << "\n\tFPS: " << fps;
            else
                cout << "\nFPS: " << fps;
        }
        /**FPS**/


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
        m_spOverlayManager->draw();// \n m_spWindow->setView(m_spWindow->getDefaultView());///draw stuff that is on hud///this doesn't appear to do anything anymore

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
    panelData.size = sf::Vector2f(500,500);
    panelData.type = ClassType::PANEL;

    leon::Panel* panel = new leon::Panel(m_spOverlayManager->getGui(), panelData);

    leon::ButtonData buttonData;
    buttonData.size = sf::Vector2f(100,50);
    buttonData.buttonText = "Exit";
    buttonData.position = sf::Vector2f(0, 0);
    buttonData.type = ClassType::BUTTON;
    Courier* pCourier = new Courier();
    sf::Packet pack;
    pack << "packet data";
    pCourier->condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    pCourier->package.reset("Static_Chunk_1", "message", pack, 0, Destination::UNIVERSE, false);
    buttonData.spCourierList.push_back(tr1::shared_ptr<Courier>(pCourier));

    leon::EditBoxData editboxData;
    editboxData.startingText = "This is Here";
    editboxData.size = sf::Vector2f(400, 50);
    editboxData.position = sf::Vector2f(100,100);
    pCourier = new Courier();
    sf::Packet editBoxOutput;
    editBoxOutput << "ship_2";
    pCourier->condition.reset(Event::ReturnKeyPressed, "", 0, 'd', true);
    pCourier->package.reset("player_1", "switchLink", editBoxOutput, 0, Destination::UNIVERSE, true);
    editboxData.spCourierList.push_back(tr1::shared_ptr<Courier>(pCourier));


    leon::WidgetBase* pEditBox = new leon::EditBox(*panel->getPanelPtr(), editboxData);
    leon::WidgetBase* pButton = new leon::Button(*panel->getPanelPtr(), buttonData);
    panel->add(tr1::shared_ptr<leon::WidgetBase>(pButton));
    panel->add(tr1::shared_ptr<leon::WidgetBase>(pEditBox));
    m_spOverlayManager->add(tr1::shared_ptr<leon::Panel>(panel));


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
    /**=============================================DECORATIONS=============================================**/
    DecorationData decorDat;
    decorDat.name = "art";
    decorDat.gfxCompData.animState = AnimationState::Activated;
    decorDat.gfxCompData.position = sf::Vector2f(20, 10);
    Decoration* pDecor = new Decoration(decorDat);
    m_spUniverse->add(pDecor);

    /**=============================================DECORATIONS=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================STATIC CHUNKS=============================================**/
    /**STATIC MODULES**/
    vector<tr1::shared_ptr<GModuleData> > staticGModuleDataList;
    vector<tr1::shared_ptr<ModuleData> > staticModuleDataList;
    GModuleData solidFixtureData;
    solidFixtureData.type = ClassType::GMODULE;

    ///solidFixtureData.spCourierList.push_back( tr1::shared_ptr<Courier>(new Courier()) );
    ///Courier& cor = *solidFixtureData.spCourierList.front();
    ///sf::Packet packet;
    ///packet << "testData";
    ///cor.condition.reset(Event::Health, "97", 97, '<', true);
    ///cor.package.reset("Static_Chunk_1", "input_1", packet, 1, Destination::UNIVERSE);

    solidFixtureData.shape = Shape::OCTAGON;
    solidFixtureData.halfSize = b2Vec2(2, 5);
    solidFixtureData.color = sf::Color::Red;
    staticGModuleDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(solidFixtureData)));


    TriggerData trigDat;
    trigDat.type = ClassType::TRIGGER;
    trigDat.offset = b2Vec2(-20, 0);


    Courier* pTriggerCourier = new Courier();
    sf::Packet triggerPack;
    triggerPack << "triggered";
    pTriggerCourier->condition.reset(Event::Triggered, "50", 50, '<', true);
    pTriggerCourier->package.reset("Static_Chunk_1", "message", triggerPack, 0, Destination::UNIVERSE, false);
    trigDat.spCourierList.push_back(std::tr1::shared_ptr<Courier>(pTriggerCourier));
    staticModuleDataList.push_back( tr1::shared_ptr<ModuleData>(new TriggerData(trigDat)) );


    /**STATIC MODULES**/

    /**STATIC CHUNK**/
    ChunkData staticChunkData;
    staticChunkData.position = b2Vec2(-20,-20);
    staticChunkData.bodyType = b2BodyType::b2_staticBody;
    staticChunkData.name = "Static_Chunk_1";

    Chunk* pStaticChunk = new Chunk(staticChunkData);
    pStaticChunk->add(staticGModuleDataList);
    pStaticChunk->add(staticModuleDataList);
    m_spUniverse->add(pStaticChunk);
    /**STATIC CHUNK**/

    /**=============================================STATIC CHUNKS=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================SHIPS=============================================**/

    /**SHIP MODULES**/
    Courier* pModuleCourier = new Courier();
    sf::Packet modulePack;
    modulePack << "module health < 50";
    pModuleCourier->condition.reset(Event::Health, "50", 50, '<', true);
    pModuleCourier->package.reset("Static_Chunk_1", "message", modulePack, 0, Destination::UNIVERSE, false);




    GModuleData shipModuleData;
    shipModuleData.spCourierList.push_back(tr1::shared_ptr<Courier>(pModuleCourier));

    ModuleData hull;
    hull.type = ClassType::HULL;
    hull.shape = Shape::POLYGON;
    hull.vertices.push_back(b2Vec2(3, 5));
    hull.vertices.push_back(b2Vec2(-3, 5));
    hull.vertices.push_back(b2Vec2(-3, -5));
    hull.vertices.push_back(b2Vec2(0, -6));
    hull.vertices.push_back(b2Vec2(3, -5));
    hull.categoryBits = Category::ShipHull;
    hull.maskBits = Mask::ShipHull;
    hull.halfSize = b2Vec2(4, 4);
    hull.density = 0.0f;
    hull.butes.setBute(Butes::isDestructable, false);
    hull.butes.setBute(Butes::isSolid, true);

    ///WE NEED TO GET A STANDARD SIZE??
    vector<tr1::shared_ptr<GModuleData> > moduleList1;
    vector<tr1::shared_ptr<ModuleData> > moduleList2;

    float offsetDelta = 2*shipModuleData.halfSize.x;
    float numBoxsX = 5, numBoxsY = 13;
    for (float i=0, x=-((numBoxsX-1)/4); i<numBoxsX; ++i, x+=offsetDelta)//creates boxes in a line
    {
        for (float c=0, y=-((numBoxsY-1)/4); c<numBoxsY; ++c, y+=offsetDelta)
        {
            if((x==0) && (y==0))
            {

            }
            else if((x==0) && (y==0.5))
            {

            }
            else
            {
                shipModuleData.offset.x = x;
                shipModuleData.offset.y = y;

                moduleList1.push_back( tr1::shared_ptr<GModuleData>(new GModuleData(shipModuleData)) );
            }
        }
    }






    ArmorData armorData;

    armorData.type = ClassType::GMODULE;
    armorData.categoryBits = Category::ShipModule;
    armorData.maskBits = Mask::ShipModuleNorm;

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
    fieldCoreData.type = ClassType::FORCE;
    fieldCoreData.offset = b2Vec2(0, 0);
    fieldCoreData.fieldData.filterData.defaultsTrue = false;

    ThrusterData thrustDat;
    thrustDat.type = ClassType::THRUSTER;
    thrustDat.offset = b2Vec2(0, 0.5);
    thrustDat.force = 500;




    moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ThrusterData(thrustDat)) );
    moduleList1.push_back( tr1::shared_ptr<GModuleData>(new ForceFieldCoreData(fieldCoreData)) );
    moduleList2.push_back( tr1::shared_ptr<ModuleData>(new ModuleData(hull)) );

    /**SHIP MODULES**/


    /**SHIP CHUNKS**/
    ShipData shipDat;
    shipDat.bodyType = b2BodyType::b2_dynamicBody;
    shipDat.type = ClassType::SHIP;

    shipDat.position = b2Vec2(-5, -5);
    shipDat.name = "ship_3";
    Chunk* pChunk0 = new Ship(shipDat);
    pChunk0->add(moduleList1);
    pChunk0->add(moduleList2);
    m_spUniverse->add(pChunk0);

    shipDat.position = b2Vec2(20, -20);
    shipDat.name = "ship_2";
    Chunk* pChunk1 = new Ship(shipDat);
    pChunk1->add(moduleList1);
    pChunk1->add(moduleList2);
    m_spUniverse->add(pChunk1);

    shipDat.position = b2Vec2(-20, 20);
    shipDat.name = "ship_1";
    Chunk* pShip1 = new Ship(shipDat);
    pShip1->add(moduleList1);
    pShip1->add(moduleList2);
    m_spUniverse->add(pShip1);


   /* vector<tr1::shared_ptr<GModuleData> > moduleListAdditive1;
    for (float i=0, x=-2, y=9, numBoxsX = 1; i<numBoxsX; ++i, ++x)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleListAdditive1.push_back( tr1::shared_ptr<GModuleData>(new ArmorData(armorData)) );
    }
    vector<tr1::shared_ptr<GModuleData> > moduleListAdditive2;*/
   /* for (float i=0, x=-2, y=10, numBoxsX = 5; i<numBoxsX; ++i, ++x)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleListAdditive2.push_back( tr1::shared_ptr<GModuleData>(new ArmorData(armorData)) );
    }
    cout << "\nAdditive.";
    pChunk1->add(moduleListAdditive1);
    cout << "\nEndAdditive.";
    pChunk1->add(moduleListAdditive2);*/

    /**SHIP CHUNKS**/

    /**=============================================SHIPS=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**======================DEBRIS============================**/

    /**DEBRIS MODULES**/
    GModuleData debrisModuleData;
    debrisModuleData.categoryBits = Category::Projectile;
    debrisModuleData.maskBits = Mask::ProjectileNorm;

    vector<tr1::shared_ptr<GModuleData> > DebrisDataList;
    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));//copy constructor
    DebrisDataList.back()->offset.x = 0;
    DebrisDataList.back()->offset.y = 0;

    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));
    DebrisDataList.back()->offset.x = 2*DebrisDataList.back()->halfSize.x;
    DebrisDataList.back()->offset.y = 0;
    /**DEBRIS MODULES**/


    /**DEBRIS CHUNKS**/
    ChunkData debrisData;
    debrisData.bodyType = b2BodyType::b2_dynamicBody;
    debrisData.position.x = 50;
    debrisData.position.y = -50;
    debrisData.isBullet = true;
    debrisData.type = ClassType::CHUNK;

    Chunk* pDebrisChunk = new Chunk(debrisData);
    pDebrisChunk->add(DebrisDataList);
    m_spUniverse->add(pDebrisChunk);


    for (int i=0, x=1, y=3, numBoxs = 20; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        pDebrisChunk = new Chunk(debrisData);
        pDebrisChunk->add(DebrisDataList);
        m_spUniverse->add(pDebrisChunk);
    }
    for (int i=0, x=3, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        pDebrisChunk = new Chunk(debrisData);
        pDebrisChunk->add(DebrisDataList);
        m_spUniverse->add(pDebrisChunk);
    }
    for (int i=0, x=5, y=3, numBoxs = 1; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        debrisData.position.x = x;
        debrisData.position.y = y;
        pDebrisChunk = new Chunk(debrisData);
        pDebrisChunk->add(DebrisDataList);
        m_spUniverse->add(pDebrisChunk);
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
    m_spIOManager->setTargets();//set IO targets

    /**=================================FINALIZING LOADED STUFF===========================================**/
}
