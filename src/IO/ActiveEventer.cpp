#include "ActiveEventer.h"


#include "globals.h"
#include "IOManager.h"
using namespace std;

ActiveEventer::ActiveEventer()
{
    m_pIOManager = &game.getGameIOManager();

    if(m_pIOManager == NULL)///DEBUG
        cout << "\nError ActiveEventerCtor";
}
ActiveEventer::~ActiveEventer()
{
}
void ActiveEventer::add(const std::tr1::shared_ptr<Courier> spCourier)
{
    m_spCourierMap[spCourier->condition.getVariableName()].push_back(spCourier);
}
int ActiveEventer::amount() const
{
    return m_spCourierMap.size();
}
void ActiveEventer::event(const std::string& variable, Variable variableName)
{
    vec& rVector = m_spCourierMap[variableName];//vec is defined in class

    for(vec::iterator it = rVector.begin(); it != rVector.end(); ++it)
    {
        if((*it)->condition.evaluate(variable))//if the condition was met
        {
            std::cout << "\nHere";
            m_pIOManager->recieve((*it)->package);///CURRENT cause of crash
            if(!((*it)->condition.isRepeatable()))//and if its not repeatable, remove it from our list
            {
                rVector.erase(it);//pointer
                --it;///MAJOR POINTER PROBLEM, WE WILL GET OUT OF SCOPE POSSIBLY?

            }
        }
    }
}
