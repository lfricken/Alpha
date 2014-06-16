#include "IOManager.h"

using namespace std;

IOManager::IOManager()
{

}
IOManager::~IOManager()//unfinished
{
    //dtor
}
void IOManager::recieve(Package& rPackage)//finished
{
    m_packageletList.push_back(Packagelet(rPackage.getDelay(), rPackage.getTargetID(), rPackage.getCommand(), rPackage.getDestination(), rPackage.getParameter()));
}
void IOManager::update(float timeChange)//unfinished, cause it got f'd up by adding the address to the package USE THIS CODE FOR GAME::setAddresses!!!!@@@@
{
    for(std::vector<Packagelet>::iterator it = m_packageletList.begin(); it != m_packageletList.end(); ++it)
    {
        it->timeRemaining -= timeChange;
        if(it->timeRemaining <= 0)
        {
            /**go to the appropriate element in our IOComponentList**/
            if(it->targetID < m_IOComponentList.size())
            {
                m_IOComponentList[it->targetID]->input(it->parameter, it->command);
            }
            else
            {
                cout << "\nCouldn't find target[" << (it)->targetID << "] with command [" << it->command << "].";
                ///ERROR LOG, couldnt find a target may have been destroyed
            }

            m_packageletList.erase(it);//pointer
            --it;
        }
    }
}
IOComponent* IOManager::createIOComponent(const std::string& name)
{
    IOComponent* pIOComp = NULL;

    if(!m_IOCFreeList.empty()) /**check if there is a free IOComponent we can use**/
    {
        pIOComp = &*m_IOComponentList[m_IOCFreeList.back()];
        m_IOCFreeList.pop_back();
    }
    else /**if not, make a new one**/
    {
        pIOComp = new IOComponent(m_IOComponentList.size(), *this);
        m_IOComponentList.push_back(std::tr1::shared_ptr<IOComponent>(pIOComp));
    }
    /**set its data and return a pointer to it**/

    pIOComp->setName(name);
    return pIOComp;
}
void IOManager::setTargets()
{
    /**loop over all Couriers, which are in the IOComponents, and set their target ID's with the map**/
}
