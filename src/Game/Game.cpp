#include "Game/Game.h"

#include <globals.h>

#include <Universe/UniversalContactListener.h>
#include <Universe/DChunk.h>
#include <Universe/DGModule.h>

using namespace std;


Game::Game() :  m_gameWindow(sf::VideoMode(1300, 700), "SFML Box2D Test Environment", sf::Style::Default, settings)
{
    m_spGameIOManager = std::tr1::shared_ptr<IOManager>(new IOManager(*this));
    m_gameWindow.setFramerateLimit(60);
}
Game::~Game()//unfinished
{
    //dtor
}
IOManager& Game::getGameIOManager()
{
    return (*m_spGameIOManager);
}
sf::RenderWindow& Game::getGameWindow()
{
    return m_gameWindow;
}
void Game::run()
{
    b2World& rWorld = m_gameUniverse.getWorld();
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(1200, 600));
    UniversalContactListener contactListener;
    rWorld.SetContactListener(&contactListener);


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





    /**Solid box**/
    float solidPos = -20.0;
    float solidHalfSize = 5;
    //body
    b2BodyDef groundBodyDef;//creates a grounded body
    groundBodyDef.position.Set(solidPos, solidPos);//sets the position of the groundbody
    b2Body* groundBody = rWorld.CreateBody(&groundBodyDef);//creates a body pointer named groundBody that points to rWorld body with groundBody's properties (position)
    //fixture
    b2PolygonShape groundBox;//creates a shape named groundBox
    groundBox.SetAsBox(solidHalfSize, solidHalfSize);//makes groundBox a pBox collision shape
    groundBody->CreateFixture(&groundBox, 0.0f);//Glues the groundBox to GroundBody, the rWorld coordinate thing.


    //visuals
    sf::RectangleShape rect(sf::Vector2f(2*solidHalfSize*scale, 2*solidHalfSize*scale));
    rect.setFillColor(sf::Color::Red);
    rect.setOrigin(solidHalfSize*scale,solidHalfSize*scale);//make the origin of the pBox its center instead of its top left corner!
    rect.setPosition(solidPos*scale, solidPos*scale); //setting the position of a sfml object sets the origin to that coordinate
    //whereas the fixture is created on the body at its center.

    /**Boxs**/
    DChunk chunk(b2Vec2(-5, -5));///help is chunk and module destructor set up?
    b2Body* pBox;
    pBox = chunk.getBody();

    DGModuleData data;

    data.physicsData.density = 1.0f;
    data.physicsData.friction = 0.4f;
    data.physicsData.halfSize = b2Vec2(0.25, 0.25);
    data.physicsData.offset = b2Vec2(0, 0);
    data.physicsData.pBody = NULL;//we dont know it yet
    /**data.pTexture = NULL;**/
    data.physicsData.restitution = 0.2f;
    data.physicsData.rotation = 0.0f;

    data.graphicsData.texName = "white.png";
    data.graphicsData.texTile = sf::Vector2f(0, 0);
    data.graphicsData.texTileSize = sf::Vector2f(64, 64);
    data.graphicsData.color = sf::Color::White;


    vector<DGModuleData> moduleList1;
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
    chunk.add(moduleList1);


    vector<DChunk> chunks;

    vector<DGModuleData> dataList;
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
        chunks.push_back(DChunk(b2Vec2(x,y)));
        chunks.back().add(dataList);
    }

    for (int i=0, x=3, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        chunks.push_back(DChunk(b2Vec2(x,y)));
        chunks.back().add(dataList);
    }
    for (int i=0, x=5, y=3, numBoxs = 200; i<numBoxs; i++, x+=2, y+=2)//creates boxes in a line
    {
        chunks.push_back(DChunk(b2Vec2(x,y)));
        chunks.back().add(dataList);
    }

    //pBox = chunks.back().getBody();



    /**Sim and runtime**/
    float timeStep = 1.0f / 60.0f;///this needs to be linked to frame rate
    int velocityIterations = 4;
    int positionIterations = 2;

    sf::Vector2f mouseCoord;
    sf::Event event;
    float zoomFactor = 1;
    float cameraMove = 10;
    float accel = 10;
    int mult = 40;
    bool mouseCoordZooming = true;//if true, it zooms in and out dependent on the cursor position
    bool camTrack = false;

    sf::Clock clock;
    float fps = 0;
    float firstTime = 0, secondTime = 0, keyPressTime = 0;


    while (m_gameWindow.isOpen())
    {
        /**CONTROL BOX**/
        secondTime = clock.getElapsedTime().asSeconds();
        fps = 1.0f / (secondTime - firstTime);
        firstTime = clock.getElapsedTime().asSeconds();




        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            float fX = accel*mult*sin(pBox->GetAngle());
            float fY = accel*mult*cos(pBox->GetAngle());
            pBox->ApplyForce(b2Vec2(fX,-fY),pBox->GetWorldCenter(), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            pBox->ApplyTorque(-accel*mult/5, true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            float fX = accel*mult*sin(pBox->GetAngle());
            float fY = accel*mult*cos(pBox->GetAngle());
            pBox->ApplyForce(b2Vec2(-fX,fY),pBox->GetWorldCenter(), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            pBox->ApplyTorque(accel*mult/5, true);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            cout << "\n\n\nExiting...\n\n";
            return;
        }
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

//CONTROL ALL chunks list
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        {
            for(vector<DChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
            {
                it->getBody()->ApplyForce(b2Vec2(0,-accel),it->getBody()->GetWorldCenter(), false);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            for(vector<DChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
            {
                it->getBody()->ApplyForce(b2Vec2(-accel,0),it->getBody()->GetWorldCenter(), true);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            for(vector<DChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
            {
                it->getBody()->ApplyForce(b2Vec2(0,accel),it->getBody()->GetWorldCenter(), true);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            for(vector<DChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
            {
                it->getBody()->ApplyForce(b2Vec2(accel,0),it->getBody()->GetWorldCenter(), true);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            for(vector<DChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
            {
                it->getBody()->ApplyForce(b2Vec2(-accel,-accel),it->getBody()->GetWorldCenter(), true);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            cout << "\nFPS: " << fps;
            cout << "\nMouse: (" << mouseCoord.x << "," << mouseCoord.y << ")";
            cout << "\nZoom: " << zoomFactor;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ((clock.getElapsedTime().asSeconds()-keyPressTime) > 0.25))
        {
            keyPressTime = clock.getElapsedTime().asSeconds();
            view1.setRotation(0.0f);
            camTrack = !camTrack;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && ((clock.getElapsedTime().asSeconds()-keyPressTime) > 0.25))
        {
            keyPressTime = clock.getElapsedTime().asSeconds();
        }


//MOUSE MOVEMENT
        while (m_gameWindow.pollEvent(event))//zoom stuff
        {
            if (event.type == sf::Event::Closed)
                m_gameWindow.close();

            if (event.type == sf::Event::MouseMoved)
            {
                mouseCoord = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                mouseCoord = m_gameWindow.mapPixelToCoords((sf::Vector2i)mouseCoord);
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                float zoomChange = event.mouseWheel.delta;
                if (zoomChange > 0)
                    zoomChange = 0.5;
                else if (zoomChange < 0)
                    zoomChange = 2.0;

                cameraMove *= zoomChange;
                zoomFactor *= zoomChange;
                view1.zoom(zoomChange);
                cout << "\nZoom Level: " << zoomFactor;

                if(mouseCoordZooming)
                {
                    sf::Vector2f smooth = view1.getCenter();//we do this so zooming is smoother
                    view1.setCenter(sf::Vector2f( (mouseCoord.x+smooth.x)/2, (mouseCoord.y+smooth.y)/2 ));
                }
            }
        }

        rWorld.Step(timeStep, velocityIterations, positionIterations);///this needs to be linked to frame rate

        m_gameWindow.clear();

        if (camTrack)
        {
            view1.setCenter(sf::Vector2f(scale*pBox->GetPosition().x, scale*pBox->GetPosition().y));
            view1.setRotation(180.0*pBox->GetAngle()/PI);
        }



        m_gameWindow.setView(view1);
        m_gameWindow.draw(rect);

        chunk.draw();
        for(vector<DChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
        {
            it->draw();
        }


        m_gameWindow.setView(m_gameWindow.getDefaultView());//stuff that isnt resized by zoom gets put here
        convex.setPosition(m_gameWindow.mapPixelToCoords(sf::Vector2i(40,40)));
        m_gameWindow.draw(convex);


        m_gameWindow.display();
        m_gameWindow.setView(view1);//if we dont put this wierd stuff happens because the view stays as the old one
    }
}

