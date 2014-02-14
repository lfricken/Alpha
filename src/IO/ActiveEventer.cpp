#include "IO/ActiveEventer.h"

using namespace std;

ActiveEventer::ActiveEventer(IOManager& rIOManager) : m_rIOManager(rIOManager)//unfinished
{
    m_isActive = true;
    //more stuff?
}

ActiveEventer::~ActiveEventer()//unfinished
{
    //dtor
}
bool ActiveEventer::f_check(string variable, Condition& rCondition)//finished
{
    //check to see whether the var passed in satisfies the condition with an if, else if, else if, else
    if(rCondition.comparison == '=')
    {
        if(rCondition.value == variable)
        {
            return true;
        }
        return false;
    }

    float var = atof(variable.c_str());//help [::atof] vs [atof]
    float val = atof(rCondition.value.c_str());

    if(rCondition.comparison == '>')
    {
        if(var > val)
        {
            return true;
        }
        return false;
    }

    if(rCondition.comparison == '<')
    {
        if(var < val)
        {
            return true;
        }
        return false;
    }
    else
        cout <<"\nMessage Failed: [" << rCondition.comparison << "] [" << rCondition.value << "]";
}
void ActiveEventer::add(const Courier& rCourier)//finished
{
    m_courierList.push_back(rCourier);//adds the courier passed in to our list of couriers to be evented
}
int ActiveEventer::amount() const//finished
{
    return m_courierList.size();
}
void ActiveEventer::event(const string variable)//unfinished OVERLOAD me for floats, doubles, integers, and strings
{
    //loop over the conditions to see if they got activated using check, and if so, send them, if not, dont, destroy them if necessary
    for(vector<Courier>::iterator it = m_courierList.begin(); it != m_courierList.end(); ++it)
    {
        if(f_check(variable, it->condition))//if the condition was met
        {
            m_rIOManager.recieve(it->package);//send it to the IOManager to deal with
            if(!(it->condition.repeatable))//and if its not repeatable, remove it from our list
            {
                m_courierList.erase(it);//pointer
                --it;//go back one because we are now pointing at the next element (because of erase)
            }
        }
    }
}
