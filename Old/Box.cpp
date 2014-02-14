#include "Box.h"

Box::Box()
{
    cout << "\nBox created!";
}
Box::Box(float radius, b2Vec2 position, b2World& world, unsigned const int scale)
{
    cout << "\nBox created!";

    theScale = scale;

//bodt
    b2BodyDef bodyDef;//creates and sets body data
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);

    b2Body* box = world.CreateBody(&bodyDef);///Lets the world know it exists
    myPhys = box;

//fixture
    b2PolygonShape boxShape;//creates some shape named boxShape
    boxShape.SetAsBox(radius, radius, b2Vec2(radius, radius), 0);//makes the shape a box. a box2d box will be 2x as big as a sfml box of same input
    b2FixtureDef fixtureDef;//creates and sets fixture data

    fixtureDef.shape = &boxShape;//makes the shape of the fixture the same as boxShape
    fixtureDef.density = 1.0f;//default is 1
    fixtureDef.friction = 0.5f;//default friction


    //a fixture imparts a body(point entity) with the properties of a 2d physics object(fixture)
    b2Fixture* fix = box->CreateFixture(&fixtureDef);//links the fixture to the body
    //visuals:
    sf::RectangleShape graphicsShape(sf::Vector2f(2*radius*scale, 2*radius*scale));//a box2d box will be 2x as big as a sfml box of same input
    graphicsShape.setFillColor(sf::Color::Red);
    graphicsShape.setOrigin(radius*scale,radius*scale);
    myShape = graphicsShape;
}




Box::~Box()
{
    cout << "\nBox destroyed!";//we actually need more stuff here...
}

void Box::draw(sf::RenderWindow& window)
{
    my_gfx_position = myPhys->GetFixtureList()->GetAABB(0).GetCenter();
    float32 angle = 180*myPhys->GetAngle()/PI;
    myShape.setPosition(my_gfx_position.x*theScale, my_gfx_position.y*theScale);
    myShape.setRotation(angle);
    window.draw(myShape);
}
