#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "stdafx.h"
#include "Chunk.h"
#include "UniversalContactListener.h"

class Universe : public IOBase//everything that would be considered to be "real" such as a box, or a star in the background is in the Universe, everything else like HUD and menus are in OverlayManager
{
public:
    Universe();
    ~Universe();


    IOBase* getTarget(const std::string& target);
    IOBase* getTarget(unsigned int target);
    Chunk* getPhysTarget(const std::string& target);
    Chunk* getPhysTarget(unsigned int target);
    ///same with graphics

    Chunk* getForwardPhys();///gets the next element
    Chunk* getBackwardPhys();///gets the next backward element
    ///Whatever We Call This* getGfxTarget(std::string target);

    b2World& getWorld();

    void add(Chunk* pChunk);
    void add(std::tr1::shared_ptr<Chunk> spChunk);
    void removeBack();
    bool removeTarget(std::string target);
    ///void add(stuff);//overloaded so we can add things that are different

    void physStep();
    void togglePause();

    void draw();//draws everything thats drawable in universe
    void toggleDebugDraw();
protected:
private:
    UniversalContactListener m_contactListener;
    b2World m_physWorld;

    bool m_notPaused;
    bool m_normalDraw;

    float m_timeStep;///this needs to be linked to frame rate
    int m_velocityIterations;
    int m_positionIterations;
    ///std::vector<tr1::shared_ptr<Whatever We Call This> > m_gfxList; //all the objects that have graphics but no physics

    std::vector<std::tr1::shared_ptr<Chunk> > m_physList;//all the objects that have physics, and maybe graphics
};

#endif // UNIVERSE_H
