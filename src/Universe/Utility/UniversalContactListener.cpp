#include "UniversalContactListener.hpp"
#include "PhysicsBase.hpp"

using namespace std;

void UniversalContactListener::BeginContact(b2Contact* contact)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    //std::cout << "\nStart Contact.";

    fixA->startContact(fixB);
    fixB->startContact(fixA);
}
void UniversalContactListener::EndContact(b2Contact* contact)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    //std::cout << "\nEnd Contact.";

    fixA->endContact(fixB);
    fixB->endContact(fixA);
}
void UniversalContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    //std::cout << "\PreSolve.";

    fixA->preSolveContact(fixB);
    fixB->preSolveContact(fixA);
}
void UniversalContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    PhysicsBase* fixA = static_cast<PhysicsBase*>(contact->GetFixtureA()->GetUserData());
    PhysicsBase* fixB = static_cast<PhysicsBase*>(contact->GetFixtureB()->GetUserData());

    //std::cout << "\PostSolve.";

    fixA->postSolveContact(fixB);
    fixB->postSolveContact(fixA);
}
