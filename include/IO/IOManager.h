#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "stdafx.h"
#include "IOBase.h"
#include "Universe.h"
#include "OverlayManager.h"

class Game;

class IOManager
{
    public:
        IOManager(Game& game);
        ~IOManager();

        void recieve(Package& rPackage);//called by a class to give the package to us
        void update(); //iterate over the list of Packages, and if the time is up, call universe.send(Package); on that package

    protected:
    private:
        sf::Clock m_timer;
        sf::Time m_elapsedTime;
        float m_ftime;//please rename this to be more descriptive
        IOBase* m_pCurrentTarget;//pointer
        std::vector<Package> m_packageList;//list of packages to be sent

        Universe& m_rUniverse;
        OverlayManager& m_rOverlayManager;
};

#endif // IOMANAGER_H
