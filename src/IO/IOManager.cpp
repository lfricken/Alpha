#include "IOManager.h"

#include "IOComponent.h"

using namespace std;

IOManager::IOManager()
{

}
IOManager::~IOManager()//unfinished
{
    //dtor input_1
}
void IOManager::recieve(const Package& rPackage)//finished
{
    // cout << FILELINE;
    // cout << "\nCommand: " << rPackage.getCommand();
    //  cout << "\nID: " << rPackage.getTargetID();
    m_packageletList.push_back(Packagelet(rPackage.getDelay(), rPackage.getTargetID(), rPackage.getCommand(), rPackage.getDestination(), rPackage.getParameter()));
}
void IOManager::update(float timeChange)//unfinished, cause it got f'd up by adding the address to the package USE THIS CODE FOR GAME::setAddresses!!!!@@@@
{
    //cout << "\nStart IOMan update.";
    for(unsigned int i = 0; i < m_packageletList.size(); ++i)
    {
        m_packageletList[i].timeRemaining -= timeChange;
        if(m_packageletList[i].timeRemaining <= 0)
        {
            /**go to the appropriate element in our IOComponentList**/
            if(m_packageletList[i].targetID < m_IOComponentList.size())
            {
                m_IOComponentList[m_packageletList[i].targetID]->input(m_packageletList[i].parameter, m_packageletList[i].command);
            }
            else
            {
                cout << "\nCouldn't find target[" << m_packageletList[i].targetID << "] with command [" << m_packageletList[i].command << "].";
                ///ERROR LOG, couldnt find a target may have been destroyed
            }
            m_packageletList.erase(m_packageletList.begin() + i);
            --i;
        }
    }
    /**go back over the packagelets and erase the ones that are done**/

    // m_packageletList.clear();///just delete everything for now.
    //cout << "\nEnd IOMan update.";

}
IOComponent* IOManager::createIOComponent(const std::string& name)
{
    IOComponent* pIOComp = NULL;

    if(!m_IOComponentFreeList.empty()) /**check if there is a free IOComponent we can use**/
    {
        pIOComp = &*m_IOComponentList[m_IOComponentFreeList.back()];
        m_IOComponentFreeList.pop_back();
    }
    else /**if not, make a new one**/
    {
        pIOComp = new IOComponent(m_IOComponentList.size(), *this);
        m_IOComponentList.push_back(std::tr1::shared_ptr<IOComponent>(pIOComp));
    }
    /**set its data and return a pointer to it**/

    pIOComp->setName(name);
    m_nameIDMap[name] = pIOComp->getID();
    return pIOComp;
}
void IOManager::setTargets()
{
    /**loop over all Couriers, which are in the IOComponents, and set their target ID's with the map**/
    std::map<Event, CourierVector>* pMap = NULL;
    CourierVector* pVec = NULL;
    Package* pPac = NULL;
    std::string targetName;
    std::map<std::string, unsigned int>::iterator it_name;

    for(auto it_io = m_IOComponentList.begin(); it_io != m_IOComponentList.end(); ++it_io)//for each map in the IOComponents
    {
        pMap = &(*it_io)->getEventerPtr()->getCourierMap();
        for(auto it_map = pMap->begin(); it_map != pMap->end(); ++it_map)//for each vector in the maps
        {
            pVec = &it_map->second;
            for(auto it_vec = pVec->begin(); it_vec != pVec->end(); ++it_vec)//for each courier in the vectors
            {
                pPac = &(*it_vec)->package;
                targetName = pPac->getTargetName();

                it_name = m_nameIDMap.find(targetName);
                if(it_name != m_nameIDMap.end())//we found it
                    pPac->setTargetID(it_name->second);
                else//we didn't find it
                {
                    cout << "\nCould not find target [" << targetName << "]" << FILELINE;
                    pPac->setTargetID(0);
                    ///ERROR LOG
                }
            }
        }
    }
}
IOBase* IOManager::getTarget(const std::string targetName)
{
    auto it_name = m_nameIDMap.find(targetName);
    unsigned int id = it_name->second;
    return getTarget(id);
}
IOBase* IOManager::getTarget(unsigned int targetID)
{
    if(targetID < m_IOComponentList.size())
        return m_IOComponentList[targetID]->getOwner();
    else
        return NULL;
}
void IOManager::f_free(unsigned int id)
{
    m_IOComponentFreeList.push_back(id);
}
