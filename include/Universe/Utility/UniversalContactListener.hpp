#ifndef UNIVERSALCONTACTLISTENER_H
#define UNIVERSALCONTACTLISTENER_H

#include "stdafx.hpp"

class UniversalContactListener : public b2ContactListener
{
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

    protected:
    private:
};

#endif // UNIVERSALCONTACTLISTENER_H
