/**WONT BE NEEDED**/
#include "Chunk.hpp"
#include "Ship.hpp"

#include "GModule.hpp"
#include "Module.hpp"
#include "Button.hpp"
#include "Picture.hpp"
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
#include "AmmoStorage.hpp"

using namespace std;

Game::Game()
{
    m_state = Game::Status::Local;
    loadWindow();

    IOBaseData universeData;
    universeData.name = "universe";
    universeData.type = ClassType::UNIVERSE;

    m_spAnimAlloc = std::tr1::shared_ptr<AnimationAllocator>(new AnimationAllocator);
    m_spIOManager = std::tr1::shared_ptr<IOManager>(new IOManager());//independent
    m_spUniverse = std::tr1::shared_ptr<Universe>(new Universe(universeData));//needs IO Manager


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
            blurEnabled = false;
            vSinc = false;
            targetFPS = 10;
        }
        std::string windowName;//name of window to display
        std::string defaultFont;//font file
        std::string windowMode;//windowed vs fullscreen
        sf::VideoMode mode;
        int antiAliasLevel;
        bool smoothTextures;
        std::string motionBlurShader;
        bool blurEnabled;
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
        windowData.motionBlurShader = root["motionBlurFile"].asString();
        windowData.blurEnabled = root["motionBlurEnabled"].asBool();
        windowData.vSinc = root["vSinc"].asBool();
        windowData.targetFPS = root["targetFPS"].asInt();
    }

    /**LOAD DATA FROM WINDOW**/
    if (sf::Shader::isAvailable() && windowData.blurEnabled)
        m_shader.loadFromFile(windowData.motionBlurShader, sf::Shader::Fragment);


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

    m_renderTexture.create(m_spWindow->getSize().x, m_spWindow->getSize().y);

    m_spRenderSprite.reset();
    m_spRenderSprite = std::tr1::shared_ptr<sf::Sprite>(new sf::Sprite);
    m_spRenderSprite->setTexture(m_renderTexture.getTexture());
    m_spRenderSprite->setPosition(0,0);
    m_spRenderSprite->setRotation(0);
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
    m_spUniverse->togglePause(true);
    leon::Panel* pMainMenu = m_spOverlayManager->getTarget("main_menu_panel");
    if(pMainMenu != NULL)
        pMainMenu->show();
    else
        cout << FILELINE;

    /**SIMULATION & RUNTIME**/


    float fps = 0;
    float firstTime = 0, secondTime = 0, timeForFrame = 0, computeTime = 0, remainder = 0;
    int maxSteps = 7;
    int i = 0;
    /**SIMULATION & RUNTIME**/


    /**EXPERIMENTATION**/


    /**EXPERIMENTING**/

    sf::Event event;
    while(m_spWindow->isOpen() && m_state != Game::Quit)
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

        m_spControlManager->choiceUpdate(event);//if we put this before physstep, the camera lags!

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
        int color = 30;
        m_spWindow->clear();
        m_renderTexture.clear(sf::Color(color,color,color,255));

        m_spControlManager->drawUpdate();

        m_renderTexture.display();
        m_spWindow->draw(*game.m_spRenderSprite);//draw game render sprite
        m_spOverlayManager->draw();//draw hud
        m_spWindow->display();//DISPLAY IT ALL
        /**DRAW**/
    }

    return m_state;
}
float Game::getTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}
void Game::f_load(const std::string& stuff)///ITS NOT CLEAR WHAT WE ARE LOADING EXACTLY, defaults states?, maps?, screen items?
{
    (void)stuff;//shutup the compiler about unused
    sf::Packet voidPacket;
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
    /*
    tgui::Tab::Ptr tab(m_spOverlayManager->getGui());///TEMPORARY, JUST FOR TESTS, NEED TO MAKE MY OWN CONTAINER FOR THIS
    tab->load(config);
    tab->setPosition(300, 10);
    tab->add("Weapon");
    tab->add("Ammo");
    tab->add("Items");
    */




    /**===================**/
    /**=====MAIN MENU=====**/
    /**===================**/

    /**===================**/
    /**====HOW TO PLAY====**/
    /**===================**/

    /**===================**/
    /**====HOW TO PLAY====**/
    /**===================**/




    leon::PanelData mainMenuData;
    mainMenuData.name = "main_menu_panel";
    mainMenuData.backgroundTex = "textures/core/screen_1.png";
    mainMenuData.configFile = config;
    mainMenuData.position = sf::Vector2f(0, 0);
    mainMenuData.size = sf::Vector2f(1920,1080);
    mainMenuData.type = ClassType::PANEL;
    leon::Panel* pMain_menu = new leon::Panel(m_spOverlayManager->getGui(), mainMenuData);
    /**====TITLE====**/
    leon::PictureData pictureData;
    pictureData.texName = "textures/core/main_menu_logo.png";
    pictureData.configFile = config;
    pictureData.position = sf::Vector2f(20, 20);
    pictureData.size = sf::Vector2f(847,104);
    pictureData.type = ClassType::DECORATION;
    /**====RESUME====**/
    leon::ButtonData resumeButtonData;
    resumeButtonData.size = sf::Vector2f(150,50);
    resumeButtonData.buttonText = "Resume";
    resumeButtonData.position = sf::Vector2f(20, 300);
    resumeButtonData.type = ClassType::BUTTON;
    Courier resumeMessage1;
    resumeMessage1.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    resumeMessage1.package.reset("main_menu_panel", "hide", voidPacket, 0, Destination::UNIVERSE, false);
    Courier resumeMessage2;
    resumeMessage2.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    sf::Packet statePacket;
    statePacket << "Playing";
    resumeMessage2.package.reset("player_1", "setState", statePacket, 0, Destination::UNIVERSE, false);
    Courier resumeMessage3;
    resumeMessage3.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    resumeMessage3.package.reset("universe", "togglePause", voidPacket, 0, Destination::UNIVERSE, false);
    resumeButtonData.courierList.push_back(resumeMessage1);
    resumeButtonData.courierList.push_back(resumeMessage2);
    resumeButtonData.courierList.push_back(resumeMessage3);
    /**====HOW TO PLAY====**/
    leon::ButtonData htpButData;
    htpButData.size = sf::Vector2f(275,50);
    htpButData.buttonText = "How To Play";
    htpButData.position = sf::Vector2f(20, 400);
    htpButData.type = ClassType::BUTTON;
    Courier htpMessage;
    htpMessage.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    htpMessage.package.reset("ecg", "show", voidPacket, 0, Destination::UNIVERSE, false);
    htpButData.courierList.push_back(htpMessage);
    /**====EXIT====**/
    leon::ButtonData exitButtonData;
    exitButtonData.size = sf::Vector2f(100,50);
    exitButtonData.buttonText = "Exit";
    exitButtonData.position = sf::Vector2f(20, 600);
    exitButtonData.type = ClassType::BUTTON;
    Courier buttonMessage;
    buttonMessage.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    buttonMessage.package.reset("game", "exit", voidPacket, 0, Destination::UNIVERSE, false);
    exitButtonData.courierList.push_back(buttonMessage);

    leon::WidgetBase* picture = new leon::Picture(*pMain_menu->getPanelPtr(), pictureData);
    pMain_menu->add(tr1::shared_ptr<leon::WidgetBase>(picture));
    leon::WidgetBase* pResume = new leon::Button(*pMain_menu->getPanelPtr(), resumeButtonData);
    pMain_menu->add(tr1::shared_ptr<leon::WidgetBase>(pResume));
    leon::WidgetBase* pHTP = new leon::Button(*pMain_menu->getPanelPtr(), htpButData);
    pMain_menu->add(tr1::shared_ptr<leon::WidgetBase>(pHTP));
    leon::WidgetBase* pExit = new leon::Button(*pMain_menu->getPanelPtr(), exitButtonData);
    pMain_menu->add(tr1::shared_ptr<leon::WidgetBase>(pExit));

    m_spOverlayManager->add(tr1::shared_ptr<leon::Panel>(pMain_menu));
    /**===================**/
    /**=====MAIN MENU=====**/
    /**===================**/




    /**===================**/
    /**====PANEL_PANEL====**/
    /**===================**/
    leon::PanelData panel_panel;
    panel_panel.name = "panel_panel";
    panel_panel.configFile = config;
    panel_panel.backgroundColor = sf::Color(255,255,255,1);
    panel_panel.position = sf::Vector2f(0, 0);
    panel_panel.size = sf::Vector2f(150,25);
    panel_panel.type = ClassType::PANEL;
    leon::Panel* ptr_panel_panel = new leon::Panel(m_spOverlayManager->getGui(), panel_panel);

    leon::ButtonData minBut;
    minBut.size = sf::Vector2f(50,25);
    minBut.buttonText = "Admin";
    minBut.position = sf::Vector2f(0, 0);
    minBut.type = ClassType::BUTTON;
    Courier minButMessage;
    minButMessage.condition.reset(Event::LeftMouseClicked, "", 0, 'd', true);
    minButMessage.package.reset("admin_panel", "toggleHide", voidPacket, 0, Destination::UNIVERSE, false);
    minBut.courierList.push_back(minButMessage);

    leon::WidgetBase* pAdminMinBut = new leon::Button(*ptr_panel_panel->getPanelPtr(), minBut);
    ptr_panel_panel->add(tr1::shared_ptr<leon::WidgetBase>(pAdminMinBut));

    m_spOverlayManager->add(tr1::shared_ptr<leon::Panel>(ptr_panel_panel));
    /**===================**/
    /**====PANEL_PANEL====**/
    /**===================**/




    /**===================**/
    /**====ADMIN PANEL====**/
    /**===================**/
    leon::PanelData panelData;
    panelData.name = "admin_panel";
    panelData.configFile = config;
    panelData.backgroundColor = sf::Color(255,255,255,1);
    panelData.position = sf::Vector2f(300, 300);
    panelData.size = sf::Vector2f(500,500);
    panelData.type = ClassType::PANEL;
    leon::Panel* admin_panel = new leon::Panel(m_spOverlayManager->getGui(), panelData);

    leon::EditBoxData editboxData;
    editboxData.startingText = "ship_3";
    editboxData.size = sf::Vector2f(200, 50);
    editboxData.position = sf::Vector2f(0,0);
    Courier editboxMessage;
    editboxMessage.condition.reset(Event::ReturnKeyPressed, "", 0, 'd', true);
    editboxMessage.package.reset("player_1", "switchLink", voidPacket, 0, Destination::UNIVERSE, true);
    editboxData.courierList.push_back(editboxMessage);

    leon::WidgetBase* pEditBox = new leon::EditBox(*admin_panel->getPanelPtr(), editboxData);
    admin_panel->add(tr1::shared_ptr<leon::WidgetBase>(pEditBox));

    m_spOverlayManager->add(tr1::shared_ptr<leon::Panel>(admin_panel));
    /**===================**/
    /**====ADMIN PANEL====**/
    /**===================**/


    /**GUI**/
    /**=============================================GUI=============================================**/
///==============================================================================
///==============================================================================
///==============================================================================
    /**=============================================DECORATIONS=============================================**/
    DecorationData decorDat;
    decorDat.gfxCompData.dimensions = sf::Vector2f(128, 128);
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
    GModuleData shipModuleData;

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
            else if((x==-1) && (y==-0.5))
            {

            }
            else if((x==0) && (y==-0.5))
            {

            }
            else if((x==-1) && (y==-3.0))
            {

            }
            else if((x==1) && (y==-3.0))
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
    AmmoStorageData ammoData;
    ammoData.offset.x = -1;
    ammoData.offset.y = -0.5;

    CapacitorData capData;
    CapacitorData capData2;
    capData.offset = b2Vec2(0, 2.5);
    capData2.offset = b2Vec2(0, -0.5);

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


    ThrusterData thrustDat1;
    thrustDat1.offset = b2Vec2(-1.0, -3.0);
    ThrusterData thrustDat2;
    thrustDat2.offset = b2Vec2(1.0, -3.0);

    RadarData radarDat;
    radarDat.offset.x = 1;
    radarDat.offset.y = -0.5;




    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ThrusterData(thrustDat1)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ThrusterData(thrustDat2)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ForceFieldCoreData(fieldCoreData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new TurretData(turretData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new TurretData(turretData2)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new TurretData(turretData3)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new CapacitorData(capData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new CapacitorData(capData2)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new ReactorData(reacData)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new RadarData(radarDat)) );
    moduleList1.push_back( tr1::shared_ptr<const GModuleData>(new AmmoStorageData(ammoData)) );

    moduleList2.push_back( tr1::shared_ptr<const ModuleData>(new HullData(hull)) );

    /**SHIP MODULES**/


    /**SHIP CHUNKS**/
    ShipData shipDat;
    shipDat.bodyType = b2BodyType::b2_dynamicBody;
    shipDat.type = ClassType::SHIP;
    shipDat.ammoGrouping.getAmmo(AmmoType::MediumShell).changeValue(100);

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
    debrisModuleData.animationFileName = "textures/asteroid.acfg";
    debrisModuleData.texName = "textures/asteroid.png";

    vector<tr1::shared_ptr<const GModuleData> > DebrisDataList;
    debrisModuleData.offset.x = 0;
    debrisModuleData.offset.y = 0;
    DebrisDataList.push_back(tr1::shared_ptr<GModuleData>(new GModuleData(debrisModuleData)));//copy constructor

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
void Game::setStatus(Game::Status newStatus)
{
    m_state = newStatus;
}
void Game::reloadWindow()
{
    loadWindow();
    auto& rPlayerList = m_spControlManager->getPlayerList();
    for(auto it = rPlayerList.begin(); it!=rPlayerList.end(); ++it)
    {
        (*it)->getCamera().resetZoom();
        (*it)->getCamera().resetViewport();
    }
}
sf::RenderTarget& Game::getRenderTarget()
{
    return m_renderTexture;
}
IOBaseReturn Game::input(IOBaseArgs)
{
    (void)rInput;//shutup the compiler about unused vars
    if(rCommand == "reloadWindow")
        reloadWindow();
    else if(rCommand == "exit")
        setStatus(Game::Status::Quit);
    else
    {
        ///ERROR LOG
        std::cout << "\nCommand [" << rCommand << "] was never found.";
    }
}
