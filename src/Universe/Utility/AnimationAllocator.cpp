#include "AnimationAllocator.hpp"

AnimationAllocator::AnimationAllocator()
{
    /**
    std::tr1::shared_ptr<AnimSet> spBackupSet(new AnimSet);
    spBackupSet->delay = 1;
    spBackupSet->nextState = "";
    spBackupSet->sequence.push_back(sf::Vector2f(0,0));
    m_animationSets["BackupHardCodedAnimSet"] = spBackupSet;**/
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
    {
        constAnimSetPtr = &*(it_find->second);
    }
    else//if it doesn't exist
    {

        std::tr1::shared_ptr<AnimSet> sharedPtr(new AnimSet);
        Json::Value root;//Let's parse it
        Json::Reader reader;
        std::ifstream test(rFileName, std::ifstream::binary);
        parsedSuccess = reader.parse(test, root, false);

        if(parsedSuccess)
        {
            std::vector<int> copyPositions;//positions of settings that need a copy of another setting
            const Json::Value stateList = root["stateList"];

            int counter = 0;
            for(auto it = stateList.begin(); it != stateList.end(); ++it)//get all the state settings
            {
                if(not (*it)["copyFrom"].isNull())//check if we have some value to copy from
                {
                    copyPositions.push_back(counter);//store us for later
                }
                else//copy that data to one of our animation states
                {
                    AnimationSetting setting;
                    setting.delay = (*it)["delay"].asFloat();
                    setting.nextState = (*it)["nextState"].asString();
                    setting.texTileSize = sf::Vector2f(root["texTileSize"][0].asInt(), root["texTileSize"][1].asInt());

                    const Json::Value tileList = (*it)["tileList"];
                    for(unsigned int i = 0; i<tileList.size(); i+=2)
                    {
                        setting.sequence.push_back(sf::Vector2f(tileList[i].asInt(), tileList[i+1].asInt()));
                    }

                    (*sharedPtr)[(*it)["state"].asString()] = setting;
                }
                ++counter;
            }


            for(auto it = copyPositions.begin(); it != copyPositions.end(); ++it)
            {
                (*sharedPtr)[stateList[*it]["animState"].asString()] = (*sharedPtr)[stateList[*it]["copyFrom"].asString()];
            }

            m_animationSets[rFileName] = sharedPtr;//if everything went right, we can add it to our list
            constAnimSetPtr = &*(m_animationSets[rFileName]);
        }
        else//we failed to parse successfully
        {
            std::cout << "\nFailed to parse JSON file [" << rFileName << "]." << std::endl << FILELINE;
            ///ERROR LOG

            constAnimSetPtr = this->requestPtr("textures/default.acfg");///why doesn't this work, this causes crash?
        }
    }

    return constAnimSetPtr;
}
