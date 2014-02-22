#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <stdafx.h>

#include <Chunk.h>

class Universe : public IOBase//everything that would be considered to be "real" such as a box, or a star in the background is in the Universe, everything else like HUD and menus are in OverlayManager
{
    public:
        Universe();
        ~Universe();


        IOBase* getTarget(std::string target);//returns a pointer to the target object
        b2World& getWorld();

        void add(Chunk* pChunk);
        void draw();//draws everything thats drawable in universe
        ///void add(stuff);//overloaded so we can add things that are different

    protected:
    private:
        b2World m_physWorld;

        std::vector<std::tr1::shared_ptr<Chunk> > m_physList;//all the objects that have physics, and maybe graphics
        ///std::vector<tr1::shared_ptr<Whatever We Call This> > m_gfxList; //all the objects that have graphics but no physics
};

#endif // UNIVERSE_H
