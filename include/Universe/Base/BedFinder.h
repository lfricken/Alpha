#ifndef BEDFINDER_H
#define BEDFINDER_H

#include "stdafx.h"

/**purpose of bedFinder is to find a place to put sleeping things**/
class BedFinder
{
    public:
        BedFinder();
        virtual ~BedFinder();

        const b2Vec2& getSleepPosition();//world coordinates. gives a new spot to sleep in
        void free(const b2Vec2& pos);//world coordinates. called by the object that was woken, gives it's current sleep position
    protected:
    private:
        ///list of open spots
        std::vector<b2Vec2> m_freeSpots;
        b2Vec2 m_tempPos;
        unsigned int m_latestIndex;
        const int m_offset = 10;
};

#endif // BEDFINDER_H
