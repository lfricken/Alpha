#include "AnimationAllocator.hpp"

AnimationAllocator::AnimationAllocator()
{
    std::tr1::shared_ptr<AnimSet> spBackupSet(new AnimSet);
    spBackupSet->delay = 1;
    spBackupSet->nextState = "";
    spBackupSet->sequence.push_back(sf::Vector2f(0,0));
    m_animationSets["BackupHardCodedAnimSet"] = spBackupSet;
}
AnimationAllocator::~AnimationAllocator()
{

}
const AnimSet* AnimationAllocator::requestPtr(const std::string& rFileName)
{
    const AnimSet* constAnimSetPtr = NULL;
    auto it_find = m_animationSets.find(rFileName);
    bool parsedSuccess;

    if(it_find != m_animationSets.end())//if it exists
        constAnimSetPtr = &*(it_find->second);
    else//if it doesn't exist
    {
        AnimSet* pSettingsList = new AnimSet;
        m_animationSets[rFileName] = std::tr1::shared_ptr<AnimSet>(pSettingsList);
        Json::Value root;//Let's parse it
        Json::Reader reader;
        std::ifstream test(rFileName, std::ifstream::binary);
        parsedSuccess = reader.parse(test, root, false);

        if(parsedSuccess)
        {
            std::vector<int> copyPositions;
            const Json::Value stateList = root["stateList"];

            int counter = 0;
            for(auto it = stateList.begin(); it != stateList.end(); ++it)//get all the state settings
            {
                if(not (*it)["copyFrom"].isNull())//check if we have some value to copy from
                {
                    std::cout << "\nWill Copy.";
                    copyPositions.push_back(counter);//store us for later
                }
                else//copy that data to one of our animation states
                {
                    AnimationSetting setting;
                    setting.delay = (*it)["delay"].asFloat();
                    setting.nextState = (*it)["nextState"].asString();

                    const Json::Value tileList = (*it)["tileList"];
                    for(unsigned int i = 0; i<tileList.size(); i+=2)
                    {
                        setting.sequence.push_back(sf::Vector2f(tileList[i].asInt(), tileList[i+1].asInt()));
                    }

                    (*pSettingsList)[(*it)["state"].asString()] = setting;
                }
                ++counter;
            }


            for(auto it = copyPositions.begin(); it != copyPositions.end(); ++it)
            {
                (*pSettingsList)[stateList[*it]["animState"].asString()] = (*pSettingsList)[stateList[*it]["copyFrom"].asString()];
            }
            constAnimSetPtr = &*(m_animationSets[rFileName]);
        }
        else//we failed to parse successfully
        {
            std::cout << "\nFailed to parse JSON " << std::endl << FILELINE;
            ///ERROR LOG
            constAnimSetPtr = &*m_animationSets["BackupHardCodedAnimSet"];
        }
    }

    return constAnimSetPtr;
}
