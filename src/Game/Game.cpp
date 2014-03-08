#include "Game/Game.h"

#include <globals.h>

#include <Universe/Chunk.h>
#include <Universe/GModule.h>
#include <DebugDraw.h>

using namespace std;


Game::Game()
{
    m_spGameIOManager = std::tr1::shared_ptr<IOManager>(new IOManager(*this));
    m_settings.antialiasingLevel = 4;
    ///load data into settings, and launch window with the settings

    m_spGameWindow = std::tr1::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1200, 600), "SFML Box2D Test Environment", sf::Style::Default, m_settings));
    m_spGameWindow->setFramerateLimit(60);


    m_spGameControlManager = std::tr1::shared_ptr<ControlManager>(new ControlManager);
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
    return (*m_spGameIOManager);
}
sf::RenderWindow& Game::getGameWindow()
{
    return *m_spGameWindow;
}
TextureAllocator& Game::getTextureAllocator()
{
    return m_texAlloc;
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
    b2World& rWorld = m_gameUniverse.getWorld();
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(1200, 600));


    DebugDraw debugDrawInstance;
    rWorld.SetDebugDraw(&debugDrawInstance);
    debugDrawInstance.SetFlags(b2Draw::e_shapeBit);
    f_load("stuff");
    m_spGameControlManager->getPlayer("player_1").target = m_gameUniverse.getPhysTarget("ship_1");

    /**HUD**/
    sf::ConvexShape convex;
    // resize it to 5 points
    convex.setPointCount(5);
    // define the points
    convex.setPoint(0, sf::Vector2f(0, 0));
    convex.setPoint(1, sf::Vector2f(150, 10));
    convex.setPoint(2, sf::Vector2f(60, 30));
    convex.setPoint(3, sf::Vector2f(30, 100));
    convex.setPoint(4, sf::Vector2f(0, 50));




    b2Body* pBox = m_gameUniverse.getPhysTarget("ship_1")->getBody();

    /**SIMULATION & RUNTIME**/
    float cameraMove = 10;
    float accel = 10;
    int mult = 40;

    sf::Vector2f mouseCoord;
    sf::Event event;
    float zoomFactor = 1;
    bool mouseCoordZooming = true;//if true, it zooms in and out dependent on the cursor position
    bool camTrack = false;
    bool flip = false;

    Game::Status newState = Game::Local;
    sf::Clock clock;
    float fps = 0;
    float firstTime = 0, secondTime = 0, keyPressTime = 0;

    sf::Vector2f texTileVec(0,0);

    while (m_spGameWindow->isOpen() && newState != Game::Quit)
    {
        secondTime = clock.getElapsedTime().asSeconds();
        fps = 1.0f / (secondTime - firstTime);
        firstTime = clock.getElapsedTime().asSeconds();

        if(m_spGameControlManager->choiceUpdate())
            newState = Game::Quit;

/**INPUT===============================================================================**/
        /**CONTROL A BOX**/


        /**CAMERA MOVE**/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            view1.move(0.0, -cameraMove);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            view1.move(0.0, cameraMove);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            view1.move(-cameraMove, 0.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            view1.move(cameraMove, 0.0);
        }


        /**SPECIAL**/


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            cout << "\nFPS: " << fps;
        }


        /**DELETE STUFF**/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && ((clock.getElapsedTime().asSeconds()-keyPressTime) > 0.25))
        {
            keyPressTime = clock.getElapsedTime().asSeconds();
            cout << "\nOwnership Switch";
            flip = !flip;
            if(flip)
                pBox = m_gameUniverse.getPhysTarget("ship_1")->getBody();
            else
                pBox = m_gameUniverse.getPhysTarget("ship_2")->getBody();
        }

/**INPUT============================================================================END**/




        /**PHYSICS STEP**/
        m_gameUniverse.physStep();



        /**DRAW**/
        m_spGameWindow->clear();
        m_spGameControlManager->drawUpdate();


        /**HUD**/
        m_spGameWindow->setView(m_spGameWindow->getDefaultView());//draw stuff that is abnormal
        convex.setPosition(m_spGameWindow->mapPixelToCoords(sf::Vector2i(40,40)));
        m_spGameWindow->draw(convex);


        m_spGameWindow->display();
    }

    return newState;
}




void Game::f_load(std::string stuff)///ITS NOT CLEAR WHAT WE ARE LOADING EXACTLY
{
    /**STATIC CHUNKS**/

    float solidPos = -20.0;

    Chunk* temp = new Chunk(b2Vec2(solidPos,solidPos), b2_staticBody);



    vector<GModuleData> gModuleList3;
    GModuleData solidFixture;
    solidFixture.type = "GModule";
    solidFixture.physicsData.density = 1.0f;
    solidFixture.physicsData.friction = 0.4f;
    solidFixture.physicsData.halfSize = b2Vec2(5, 5);
    solidFixture.physicsData.offset = b2Vec2(0, 0);
    solidFixture.physicsData.pBody = NULL;//we dont know it yet
    solidFixture.physicsData.restitution = 0.2f;
    solidFixture.physicsData.rotation = 0.0f;
    solidFixture.graphicsData.texName = "textures/tileset.png";
    solidFixture.graphicsData.texTile = sf::Vector2f(0, 0);
    solidFixture.graphicsData.texTileSize = sf::Vector2f(64, 64);
    solidFixture.graphicsData.color = sf::Color::Red;

    gModuleList3.push_back(solidFixture);
    temp->add(gModuleList3);
    m_gameUniverse.add(tr1::shared_ptr<Chunk>(temp));


    /**DYNAMIC CHUNKS**/
    Chunk* chunk = new Chunk(b2Vec2(-5, -5));
    Chunk* chunk1 = new Chunk(b2Vec2(20, -20));
    //Chunk chunk(b2Vec2(-5, -5));///help is chunk and module destructor set up?

    chunk->setTargetName("ship_1");
    chunk1->setTargetName("ship_2");

    GModuleData data;
    data.type = "GModule";
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
    mdata.type = "Module";
    mdata.physicsData.density = 1.0f;
    mdata.physicsData.friction = 0.4f;
    mdata.physicsData.halfSize = b2Vec2(0.25, 0.25);
    mdata.physicsData.offset = b2Vec2(0, -5);
    mdata.physicsData.pBody = NULL;//we dont know it yet
    mdata.physicsData.restitution = 0.2f;
    mdata.physicsData.rotation = 0.0f;


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
    data.targetName = "GM01";
    data.physicsData.offset.y = 5;
    moduleList1.push_back(data);
    moduleList2.push_back(mdata);
    //chunk->add(moduleList2);
    chunk->add(moduleList1);
    chunk1->add(moduleList1);


    vector<GModuleData> dataList;
    dataList.push_back(data);
    dataList.back().physicsData.offset.x = 0;
    dataList.back().physicsData.offset.y = 0;
    dataList.back().graphicsData.texTile.x = 0;

    dataList.push_back(data);
    dataList.back().graphicsData.texTile.x = 1;
    dataList.back().physicsData.offset.x = offsetDelta;
    dataList.back().physicsData.offset.y = 0;

    for (int i=0, x=1, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        temp = new Chunk(b2Vec2(x,y), b2_dynamicBody);
        temp->add(dataList);
        m_gameUniverse.add(tr1::shared_ptr<Chunk>(temp));
    }

    for (int i=0, x=3, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        temp = new Chunk(b2Vec2(x,y), b2_dynamicBody);
        temp->add(dataList);
        m_gameUniverse.add(tr1::shared_ptr<Chunk>(temp));
    }
    for (int i=0, x=5, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        temp = new Chunk(b2Vec2(x,y), b2_dynamicBody);
        temp->add(dataList);
        m_gameUniverse.add(tr1::shared_ptr<Chunk>(temp));
    }
    m_gameUniverse.add(tr1::shared_ptr<Chunk>(chunk1));
    m_gameUniverse.add(tr1::shared_ptr<Chunk>(chunk));


}
