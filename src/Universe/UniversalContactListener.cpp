#include "UniversalContactListener.h"
#include "PhysicsBase.h"
#include "GModule.h"

using namespace std;

void UniversalContactListener::BeginContact(b2Contact* contact)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    fixA->contact(fixB);
    fixB->contact(fixA);
}
void UniversalContactListener::EndContact(b2Contact* contact)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    fixA->endContact(fixB);
    fixB->endContact(fixA);
}
