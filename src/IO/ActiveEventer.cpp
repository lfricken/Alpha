#include "ActiveEventer.h"


#include "globals.h"
#include "IOManager.h"
using namespace std;

ActiveEventer::ActiveEventer()
{
    m_pIOManager = &game.getGameIOManager();

    if(m_pIOManager == NULL)///DEBUG //sometimes we may not get created after GameIOManager so...
    {
        ///ERROR LOG
    }
}
ActiveEventer::~ActiveEventer()
{
}
void ActiveEventer::add(const std::tr1::shared_ptr<Courier> spCourier)
{
    m_spCourierMap[spCourier->condition.getEventName()].push_back(spCourier);
}
void ActiveEventer::event(const std::string& variable, Event variableName)
{
    std::map<Event, CourierVector>::iterator it_map = m_spCourierMap.find(variableName);

    if(it_map != m_spCourierMap.end())//if we found the element...
    {
        CourierVector& rVector = m_spCourierMap[variableName];//CourierVector is defined in header of Active Eventer

        for(CourierVector::iterator it = rVector.begin(); it != rVector.end(); ++it)
        {
            if((*it)->condition.evaluate(variable))//if the condition was met
            {
                m_pIOManager->recieve((*it)->package);
                if(!((*it)->condition.isRepeatable()))//and if the event isn't repeatable, remove it from our list
                {
                    rVector.erase(it);//pointer
                    --it;///MAJOR POINTER PROBLEM, WE WILL GET OUT OF SCOPE POSSIBLY? NEEDS RESOLUTION
                }
            }
        }
    }
}
