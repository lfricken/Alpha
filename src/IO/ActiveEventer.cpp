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
    m_spCourierMap[spCourier->condition.getEventName()].push_back(std::tr1::shared_ptr<Courier>( new Courier(*spCourier)));
}
void ActiveEventer::addList(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList)
{
    for(auto it = spCourierList.begin(); it != spCourierList.end(); ++it)
        add(*it);
}
void ActiveEventer::event(const std::string& rVariable, Event variableName)
{
    std::map<Event, CourierVector>::iterator it_map = m_spCourierMap.find(variableName);

    if(it_map != m_spCourierMap.end())//if we found the element...
    {
        CourierVector& rVector = m_spCourierMap[variableName];//CourierVector is defined in header of Active Eventer

        for(unsigned int i = rVector.size()-1; i < rVector.size(); ++i)
        {
            if(rVector[i]->condition.evaluate(rVariable))//if the condition was met
            {
                if(rVector[i]->condition.getComparison() == 'v')//if we should be sending the current data
                {
                    sf::Packet temp;
                    temp << rVariable;
                    rVector[i]->package.setParameter(temp);
                }


                m_pIOManager->recieve(rVector[i]->package);
                if(!(rVector[i]->condition.isRepeatable()))//and if the event isn't repeatable, remove it from our list
                {
                    rVector.erase(rVector.begin()+i);//pointer
                    --i;///MAJOR POINTER PROBLEM, WE WILL GET OUT OF SCOPE POSSIBLY? NEEDS RESOLUTION
                }
            }
        }
    }
}
std::map<Event, CourierVector>& ActiveEventer::getCourierMap()
{
    return m_spCourierMap;
}
