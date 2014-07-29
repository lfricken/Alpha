#include "BedFinder.h"

BedFinder::BedFinder()
{
    m_latestIndex = 0;
}
BedFinder::~BedFinder()
{

}
const b2Vec2& BedFinder::getSleepPosition()
{
    /**if we have open spots, use those**/
    if(!m_freeSpots.empty())
    {
        m_tempPos = m_freeSpots.back();
        m_freeSpots.pop_back();
        return m_tempPos;
    }
    else/**create a new position using equation**/
    {
        m_tempPos.x = -10000 + m_offset*m_latestIndex;
        m_tempPos.y = -10000;
        ++m_latestIndex;
        return m_tempPos;
    }
}
void BedFinder::free(const b2Vec2& pos)
{
    m_freeSpots.push_back(pos);
}
