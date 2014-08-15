/**WONT BE NEEDED**/
#include "Chunk.hpp"
#include "Ship.hpp"

#include "GModule.hpp"
#include "Module.hpp"
#include "Button.hpp"
/**WONT BE NEEDED**/

#include "Sort.hpp"
#include "Game.hpp"
#include "globals.hpp"
#include "IOManager.hpp"
#include "ControlManager.hpp"

#include "Hull.hpp"
#include "Armor.hpp"
#include "ForceFieldCore.hpp"
#include "Thruster.hpp"
#include "Turret.hpp"
#include "Capacitor.hpp"
#include "Reactor.hpp"
#include "Radar.hpp"

#include "EditBox.hpp"
#include "Decoration.hpp"
#include "ProjectileBarrel.hpp"
#include "TriangleFan.h"

using namespace std;

Game::Game()
{
    loadWindow();

    rendText_1.create(m_spWindow->getSize().x, m_spWindow->getSize().y);
    rendText_2.create(m_spWindow->getSize().x, m_spWindow->getSize().y);

    if (sf::Shader::isAvailable())
    {
        std::cout << "\nShaders are available!.";
        m_shader.loadFromFile("test.frag", sf::Shader::Fragment);

        m_vecFieldShader.loadFromFile("vectorField.frag", sf::Shader::Fragment);
        m_blurShader.loadFromFile("blur.frag", sf::Shader::Fragment);
    }

    renderSprite_2.setTexture(rendText_2.getTexture());
    renderSprite_2.setPosition(0,0);
    renderSprite_2.setRotation(0);
    renderSprite_1.setTexture(rendText_1.getTexture());
    renderSprite_1.setPosition(0,0);
    renderSprite_1.setRotation(0);

    m_spAnimAlloc = std::tr1::shared_ptr<AnimationAllocator>(new AnimationAllocator);
    m_spIOManager = std::tr1::shared_ptr<IOManager>(new IOManager());//independent
    m_spUniverse = std::tr1::shared_ptr<Universe>(new Universe());//needs IO Manager


    /**created last**/
    m_spOverlayManager = std::tr1::shared_ptr<OverlayManager>(new OverlayManager(*m_spWindow));//needs Window and iomanager
    m_spControlManager = std::tr1::shared_ptr<ControlManager>(new ControlManager());//needs Window and Universe and GUI




    std::string loadedFont = "TGUI/fonts/DejaVuSans.ttf";

    m_spOverlayManager->getGui().setGlobalFont(loadedFont);

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
void Game::loadWindow()
{
    struct WindowInitData
    {
        WindowInitData()
        {
            windowName = "FIXME";
            windowMode = "windowed";
            mode = sf::VideoMode(640, 640, 32);
            antiAliasLevel = 0;
            smoothTextures = false;
            vSinc = false;
            targetFPS = 10;
        }
        std::string windowName;//name of window to display
        std::string defaultFont;//font file
        std::string windowMode;//windowed vs fullscreen
        sf::VideoMode mode;
        int antiAliasLevel;
        bool smoothTextures;
        bool vSinc;
        int targetFPS;
    };
    WindowInitData windowData;


    Json::Value root;//Let's parse it
    Json::Reader reader;
    std::string windowFile = "window.ini";
    std::ifstream test(windowFile, std::ifstream::binary);
    bool parsedSuccess = reader.parse(test, root, false);

    if(not parsedSuccess)
    {
        std::cout << "\nFailed to parse JSON file [" << windowFile << "]." << std::endl << FILELINE;
        ///eRROR LOG
    }
    else
    {
        windowData.windowName = root["windowName"].asString();
        windowData.defaultFont = root["defaultFont"].asString();
        windowData.windowMode = root["windowMode"].asString();
        windowData.mode = sf::VideoMode(root["resX"].asInt(), root["resY"].asInt(), root["color"].asInt());
        windowData.antiAliasLevel = root["antiAliasLevel"].asInt();
        windowData.smoothTextures = root["smoothTextures"].asBool();
        windowData.vSinc = root["vSinc"].asBool();
        windowData.targetFPS = root["targetFPS"].asInt();
    }

    /**LOAD DATA FROM WINDOW**/
    m_settings.antialiasingLevel = windowData.antiAliasLevel;
    int style;//the sf::style enum has no name!!
    if(windowData.windowMode == "windowed")//windowed or fullscreen?
    {
        style = sf::Style::Default;
    }
    else
    {
        style = sf::Style::Fullscreen;
    }


    /**CREATE THE WINDOW AND TEXTURE ALLOC**/
    if(m_spWindow)//if we are already pointing at something
    {
        ///close the old window???
        m_spWindow->create(windowData.mode, windowData.windowName, style, m_settings);
        m_spTexAlloc->smoothTextures(windowData.smoothTextures);
    }
    else//if this is the first time we created something
    {
        m_spWindow.reset(new sf::RenderWindow(windowData.mode, windowData.windowName, style, m_settings));
        m_spTexAlloc.reset(new TextureAllocator(windowData.smoothTextures));
    }

    m_spWindow->setVerticalSyncEnabled(windowData.vSinc);
    m_spWindow->setFramerateLimit(windowData.targetFPS);

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
AnimationAllocator& Game::getAnimationAllocator()
{
    return *m_spAnimAlloc;
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
    int maxSteps = 7;
    int i = 0;
    /**SIMULATION & RUNTIME**/


    /**EXPERIMENTATION**/


    /**EXPERIMENTING**/

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
        for(i = 0; computeTime > 0 && i < maxSteps; ++i)
        {
            m_spControlManager->pressedUpdate();//having the pressed update ensures that key commands continue throughout any time step
            computeTime -= m_spUniverse->physStep();
        }
        remainder = computeTime;

        if(remainder > 0)
            cout << endl << remainder;

        m_spIOManager->update(timeForFrame);
        /**INPUT and PHYSICS**/

        /**DRAW**/
        m_spWindow->clear();

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
    (void)stuff;//shutup the compiler about unused
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

    /**GUI**/
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
    Courier buttonMessage;
    sf::Packet pack;
    pack << "packet data";
    buttonMessage.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    buttonMessage.package.reset("Static_Chunk_1", "message", pack, 0, Destination::UNIVERSE, false);
    buttonData.courierList.push_back(buttonMessage);

    leon::EditBoxData editboxData;
    editboxData.startingText = "This is Here";
    editboxData.size = sf::Vector2f(400, 50);
    editboxData.position = sf::Vector2f(100,100);
    Courier editboxMessage;
    sf::Packet editBoxOutput;
    editBoxOutput << "ship_2";
    editboxMessage.condition.reset(Event::ReturnKeyPressed, "", 0, 'd', true);
    editboxMessage.package.reset("player_1", "switchLink", editBoxOutput, 0, Destination::UNIVERSE, true);
    editboxData.courierList.push_back(editboxMessage);


    leon::WidgetBase* pEditBox = new leon::EditBox(*panel->getPanelPtr(), editboxData);
    leon::WidgetBase* pButton = new leon::Button(*panel->getPanelPtr(), buttonData);
    panel->add(tr1::shared_ptr<leon::WidgetBase>(pButton));
    panel->add(tr1::shared_ptr<leon::WidgetBase>(pEditBox));
    m_spOverlayManager->add(tr1::shared_ptr<leon::Panel>(panel));


    /**GUI**/
    /**=============================================GUI=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================DECORATIONS=============================================**/
    DecorationData decorDat;
    decorDat.gfxCompData.scale = sf::Vector2f(1, 1);
    decorDat.name = "art";
    decorDat.gfxCompData.rotation = 20;
    decorDat.gfxCompData.animState = "Activated";
    decorDat.gfxCompData.position = sf::Vector2f(20, 10);
    Decoration* pDecor = new Decoration(decorDat);
    m_spUniverse->add(pDecor);

    /**=============================================DECORATIONS=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================STATIC CHUNKS=============================================**/
    /**STATIC MODULES**/
    vector<tr1::shared_ptr<const GModuleData> > staticGModuleDataList;
    vector<tr1::shared_ptr<const ModuleData> > staticModuleDataList;
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
    trigDat.offset = b2Vec2(-20, 0);
    trigDat.filterData.defaultsTrue = true;


    Courier triggerMessage;
    sf::Packet triggerPack;
    triggerPack << "triggered";
    triggerMessage.condition.reset(Event::Triggered, "50", 50, '<', true);
    triggerMessage.package.reset("Static_Chunk_1", "message", triggerPack, 0, Destination::UNIVERSE, false);
    trigDat.courierList.push_back(triggerMessage);
    staticModuleDataList.push_back(tr1::shared_ptr<const ModuleData>(new TriggerData(trigDat)));


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
    Courier deathMessage;
    sf::Packet modulePack;
    modulePack << "module health < 50";
    deathMessage.condition.reset(Event::Health, "50", 50, '<', true);
    deathMessage.package.reset("Static_Chunk_1", "message", modulePack, 0, Destination::UNIVERSE, false);




    GModuleData shipModuleData;
    shipModuleData.courierList.push_back(deathMessage);

    HullData hull;
    hull.shape = Shape::POLYGON;
    hull.vertices.push_back(b2Vec2(3, 5));
    hull.vertices.push_back(b2Vec2(-3, 5));
    hull.vertices.push_back(b2Vec2(-3, -5));
    //hull.vertices.push_back(b2Vec2(0, -6));
    hull.vertices.push_back(b2Vec2(3, -5));


    ///WE NEED TO GET A STANDARD SIZE??
    vector<tr1::shared_ptr<const GModuleData> > moduleList1;
    vector<tr1::shared_ptr<const ModuleData> > moduleList2;

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
            else if((x==0) && (y==1))
            {

            }
            else if((x==1) && (y==2))
            {

            }
            else if((x==-1) && (y==2))
            {

            }
            else if((x==0) && (y==2.5))
            {

            }
            else if((x==0) && (y==2))
            {

            }
            else if((x==1) && (y==-0.5))
            {

            }
            else
            {
                shipModuleData.offset.x = x;
                shipModuleData.offset.y = y;

                moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new GModuleData(shipModuleData)) );
            }
        }
    }

    CapacitorData capData;
    capData.offset = b2Vec2(0, 2.5);

    ReactorData reacData;
    reacData.offset = b2Vec2(0, 2);

    ProjectileBarrelData barrelData1;
    ProjectileBarrelData barrelData2;
    barrelData1.barrelPixelOffset.y = 64;
    barrelData2.barrelPixelOffset.y = -64;
    barrelData1.barrelPixelOffset.x = -8;
    barrelData2.barrelPixelOffset.x = -8;
    barrelData1.muzzlePixelOffset.x = 64;
    barrelData2.muzzlePixelOffset.x = 64;
    TurretData turretData;
    turretData.offset = b2Vec2(0,1);
    turretData.weaponData.refireDelay = 0.8;
    turretData.weaponData.barrelData.push_back( std::tr1::shared_ptr<WeaponBarrelData>(new ProjectileBarrelData(barrelData1)) );
    turretData.weaponData.barrelData.push_back( std::tr1::shared_ptr<WeaponBarrelData>(new ProjectileBarrelData(barrelData2)) );


    FireCommand once1;
    once1.delay = 0;
    once1.barrelIndex = 0;
    turretData.weaponData.primeCommandList.push_back(once1);
    FireCommand once2;
    once2.delay = 0.1;
    once2.barrelIndex = 1;
    turretData.weaponData.primeCommandList.push_back(once2);

    TurretData turretData2(turretData);
    turretData2.offset = b2Vec2(1,2);
    TurretData turretData3(turretData);

    turretData3.offset = b2Vec2(-1,2);
    turretData3.weaponData.barrelData.clear();
    turretData3.weaponData.refireDelay = 0.8;
    turretData3.firesPrimary = false;
    turretData3.firesSecondary = true;

    barrelData1.recoilRecoverTime = 0.8;
    barrelData1.barrelPixelOffset.x = 32;
    barrelData1.barrelPixelOffset.y = 0;
    barrelData1.projectileType = 1;
    barrelData1.projectileVelocity = 200;
    turretData3.weaponData.primeCommandList.clear();

    FireCommand once3;
    once3.delay = 0;
    once3.barrelIndex = 0;
    turretData3.weaponData.secondaryCommandList.push_back(once3);
    turretData3.weaponData.barrelData.push_back( std::tr1::shared_ptr<WeaponBarrelData>(new ProjectileBarrelData(barrelData1)) );

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
        moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ArmorData(armorData)) );
    }
    for (float i=0, x=4, y=-9, numBoxsX = 19; i<numBoxsX; ++i, ++y)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ArmorData(armorData)) );
    }
    for (float i=0, x=-2, y=-9, numBoxsX = 5; i<numBoxsX; ++i, ++x)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ArmorData(armorData)) );
    }
    for (float i=0, x=-2, y=9, numBoxsX = 5; i<numBoxsX; ++i, ++x)//creates boxes in a line
    {
        armorData.offset.x = x*2*armorData.halfSize.x;
        armorData.offset.y = y*2*armorData.halfSize.y;
        //shipModuleData.texTile.x = texTile;
        moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ArmorData(armorData)) );
    }


    ForceFieldCoreData fieldCoreData;
    fieldCoreData.offset = b2Vec2(0, 0);
    fieldCoreData.forceFieldData.filterData.defaultsTrue = true;

    ThrusterData thrustDat;
    thrustDat.offset = b2Vec2(0, 0.5);



    RadarData radarDat;
    radarDat.offset.x = 1;
    radarDat.offset.y = -0.5;




    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ThrusterData(thrustDat)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ForceFieldCoreData(fieldCoreData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new TurretData(turretData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new TurretData(turretData2)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new TurretData(turretData3)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new CapacitorData(capData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ReactorData(reacData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new RadarData(radarDat)) );

    moduleList2.push_back( tr1::shared_ptr<const ModuleData>(new HullData(hull)) );

    /**SHIP MODULES**/


    /**SHIP CHUNKS**/
    ShipData shipDat;
    shipDat.bodyType = b2BodyType::b2_dynamicBody;
    shipDat.type = ClassType::SHIP;
    shipDat.ammoPool.getAmmo(AmmoType::MediumShell).add(100);

    shipDat.position = b2Vec2(-20, 20);
    shipDat.name = "ship_1";
    Chunk* pShip1 = new Ship(shipDat);
    pShip1->add(moduleList1);
    pShip1->add(moduleList2);
    m_spUniverse->add(pShip1);

    shipDat.position = b2Vec2(20, -20);
    shipDat.name = "ship_2";
    Chunk* pChunk1 = new Ship(shipDat);
    pChunk1->add(moduleList1);
    pChunk1->add(moduleList2);
    m_spUniverse->add(pChunk1);

    shipDat.position = b2Vec2(-5, -5);
    shipDat.name = "ship_3";
    Chunk* pChunk0 = new Ship(shipDat);
    pChunk0->add(moduleList1);
    pChunk0->add(moduleList2);
    m_spUniverse->add(pChunk0);


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

    vector<tr1::shared_ptr<const GModuleData> > DebrisDataList;
    debrisModuleData.offset.x = 0;
    debrisModuleData.offset.y = 0;
    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));//copy constructor

    debrisModuleData.offset.x = 2*debrisModuleData.halfSize.x;
    debrisModuleData.offset.y = 0;
    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));
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

    player1.cameraPos = b2Vec2(0, 0);
    player1.viewport = sf::FloatRect(0, 0, 1, 1);

    m_spControlManager->add(std::tr1::shared_ptr<Player>(new Player(player1)));
    /**
        PlayerData player2;
        player2.name = "player_2";
        player2.type = ClassType::PLAYER;
        player2.playerMode = PlayerMode::God;
        player2.targetName = "ship_2";

        player2.keyConfig.up = sf::Keyboard::Numpad8;
        player2.keyConfig.left = sf::Keyboard::Numpad4;
        player2.keyConfig.down = sf::Keyboard::Numpad5;
        player2.keyConfig.right = sf::Keyboard::Numpad6;

        player2.keyConfig.primary = sf::Mouse::Left;
        player2.keyConfig.secondary = sf::Mouse::Right;

        player2.cameraPos = sf::Vector2f(0, 0);
        player2.viewport = sf::FloatRect(0.5, 0, 0.5, 1);

        m_spControlManager->add(std::tr1::shared_ptr<Player>(new Player(player2)));
    **/
    /**PLAYER**/


    /**===========================PLAYER===========================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**==============================PROJECTILES===========================================**/


    for(int i = 0, num = 20; i<num; ++i)
    {
        m_spUniverse->getProjAlloc().add(0);
        m_spUniverse->getProjAlloc().add(1);
    }


    /**==============================PROJECTILES===========================================**/
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
