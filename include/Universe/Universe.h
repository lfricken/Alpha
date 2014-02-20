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

        void load(std::string filename);//l oads universe objects from a file and puts them into the universe!
        void draw();//draws everything thats drawable in universe
        ///void add(stuff);//overloaded so we can add things that are different

    protected:
    private:
        b2World m_physWorld;

        std::vector<std::tr1::shared_ptr<Chunk> > m_physList;//all the objects that have physics and or graphics
        ///std::vector<tr1::shared_ptr<Whatever We Call This> > m_gfxList; //all the objects that have graphics but no physics
        ///std::vector<(visual stuff that is some sort of chunk)> m_physList;//all the objects that have graphics and physics
};

#endif // UNIVERSE_H
