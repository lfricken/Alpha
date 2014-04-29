#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "stdafx.h"
#include "Chunk.h"
#include "UniversalContactListener.h"//END
#include "UniversalQueryCallback.h"
#include "DebugDraw.h"

class Universe : public IOBase//everything that would be considered to be "real" such as a box, or a star in the background is in the Universe, everything else like HUD and menus are in OverlayManager
{
public:
    Universe();
    ~Universe();

    IOBase* getTarget(const std::string& target);
    IOBase* getTarget(unsigned long long int targetID);
    Chunk* getPhysTarget(const std::string& target);
    Chunk* getPhysTarget(unsigned long long int targetID);
    ///same with graphics



    Chunk* getForwardPhys();///gets the next chunk element
    Chunk* getBackwardPhys();///gets the next backward chunk element
    ///Whatever We Call This* getGfxTarget(std::string target);


    b2World& getWorld();


    void add(Chunk* pChunk);
    void add(std::tr1::shared_ptr<Chunk> spChunk);
    void removeBack();
    bool removeTarget(std::string target);
    ///void add(stuff);//overloaded so we can add things that are different



    float physStep();
    void togglePause();



    void draw();//draws everything thats drawable in universe
    void toggleDebugDraw();
protected:
private:
    UniversalContactListener m_contactListener;
    DebugDraw m_debugDraw;
    b2World m_physWorld;

    bool m_notPaused;
    bool m_normalDraw;
    unsigned int m_currentIDCount;//used to assign id's to things

    int m_iterations;
    int m_maxIterations;
    float m_remainingTime;
    float m_timeStep;
    int m_velocityIterations;
    int m_positionIterations;
    ///std::vector<tr1::shared_ptr<Whatever We Call This> > m_gfxList; //all the objects that have graphics but no physics
    std::vector<std::tr1::shared_ptr<Chunk> > m_physList;//all the objects that have physics, and maybe graphics
};

#endif // UNIVERSE_H
