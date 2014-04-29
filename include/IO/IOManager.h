#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "stdafx.h"
#include "Package.h"

class Universe;
class OverlayManager;
class Game;
class IOBase;

class IOManager
{
    public:
        IOManager(Game& game);
        ~IOManager();

        void recieve(Package& rPackage);   //finished//called by a class to give the package to us
        void update(const float timeChange); //iterate over the list of Packages, and if the time is up, call universe.send(Package); on that package

    protected:
    private:
        IOBase* m_currentTarget;
        std::vector<Packagelet> m_packageletList;//list of packages to be sent

        Game* m_pGame;
        Universe* m_pUniverse;
        OverlayManager* m_pOverlayManager;
};

#endif // IOMANAGER_H
