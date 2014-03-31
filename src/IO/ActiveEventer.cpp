#include "ActiveEventer.h"


#include "globals.h"
#include "IOManager.h"
using namespace std;

ActiveEventer::ActiveEventer()
{
    m_pIOManager = &game.getGameIOManager();

    if(m_pIOManager == NULL)///DEBUG
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
    std::map<Event, vec>::iterator it_map = m_spCourierMap.find(variableName);

    if(it_map != m_spCourierMap.end())
    {
        //element found
        vec& rVector = m_spCourierMap[variableName];//vec is defined in class

        for(vec::iterator it = rVector.begin(); it != rVector.end(); ++it)
        {
            if((*it)->condition.evaluate(variable))//if the condition was met
            {
                m_pIOManager->recieve((*it)->package);
                if(!((*it)->condition.isRepeatable()))//and if its not repeatable, remove it from our list
                {
                    rVector.erase(it);//pointer
                    --it;///MAJOR POINTER PROBLEM, WE WILL GET OUT OF SCOPE POSSIBLY?
                }
            }
        }
    }
}
