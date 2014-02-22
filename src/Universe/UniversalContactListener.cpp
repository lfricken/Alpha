#include <UniversalContactListener.h>
#include <MultipleInheritance/PhysicsBase.h>
#include <GModule.h>

void UniversalContactListener::BeginContact(b2Contact* contact)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    fixA->collide(fixB);
    fixB->collide(fixA);
}
void UniversalContactListener::EndContact(b2Contact* contact)
{
    bool both = false;


    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        both = true;


    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData && both)
        true;
    ///std::cout << "\nEnd Contact!";
}
