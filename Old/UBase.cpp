#include "Universe/UBase.h"

using namespace std;

UBase::UBase(IOManager& rIOManager, sf::RenderWindow& rWindow, b2World& rPhysWorld) : IOBase(rIOManager), GraphicsBase(rWindow), PhysicsBase(rPhysWorld)//unfinished
{
    //this entity needs a body and other stuff when created
}
UBase::~UBase()//unfinished
{
    //destroy everything this object loved and cared about
}
bool UBase::damage(float damage)//finished
{
    ///do damage and return true if still alive, otherwise die
    return 1;
}
float UBase::getHealth()//finished
{
    return m_health;
}

