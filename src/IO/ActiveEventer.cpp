#include "ActiveEventer.h"
#include "globals.h"

using namespace std;

IOManager& ActiveEventer::m_rIOManager = game.getGameIOManager();

ActiveEventer::ActiveEventer()//unfinished
{
    m_isActive = true;
    //more stuff?
}

ActiveEventer::~ActiveEventer()//unfinished
{
    //dtor
}
void ActiveEventer::add(const Courier& rCourier)//finished
{
    m_courierList.push_back(rCourier);//adds the courier passed in to our list of couriers to be evented
}
int ActiveEventer::amount() const//finished
{
    return m_courierList.size();
}
void ActiveEventer::event(const std::string& variable, Variable variableName)//unfinished OVERLOAD me for floats, doubles, integers, and strings
{
    //loop over the conditions to see if they got activated using check, and if so, send them, if not, dont, destroy them if necessary
    for(vector<Courier>::iterator it = m_courierList.begin(); it != m_courierList.end(); ++it)
    {
        if(it->condition.evaluate(variable))//if the condition was met
        {
            m_rIOManager.recieve(it->package);//send it to the IOManager to deal with
            if(!(it->condition.isRepeatable()))//and if its not repeatable, remove it from our list
            {
                m_courierList.erase(it);//pointer
                --it;///MAJOR POINTER PROBLEM, WE WILL GET OUT OF SCOPE?
            }
        }
    }
}
