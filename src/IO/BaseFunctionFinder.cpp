#include "BaseFunctionFinder.h"
#include "IOBase.h"

BaseFunctionFinder::BaseFunctionFinder()
{
    /**DEFAULT STUFF**/
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("default", &IOBase::input_1));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_1", &IOBase::input_1));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_2", &IOBase::input_2));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_3", &IOBase::input_3));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_4", &IOBase::input_4));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_5", &IOBase::input_5));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_6", &IOBase::input_6));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_7", &IOBase::input_7));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_8", &IOBase::input_8));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_9", &IOBase::input_9));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_10", &IOBase::input_10));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_11", &IOBase::input_11));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_12", &IOBase::input_12));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_13", &IOBase::input_13));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_14", &IOBase::input_14));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_15", &IOBase::input_15));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_16", &IOBase::input_16));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_17", &IOBase::input_17));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_18", &IOBase::input_18));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_19", &IOBase::input_19));
    m_aliasMap.insert(std::pair<std::string, TargetFunc>("input_20", &IOBase::input_20));
}

BaseFunctionFinder::~BaseFunctionFinder()
{
}

TargetFunc BaseFunctionFinder::getFunction(const std::string& alias)
{
    if(m_aliasMap[alias])
    {
        return m_aliasMap[alias];
    }
    else
    {
        return m_aliasMap["default"];
    }
}
void BaseFunctionFinder::load(const std::string& aliasTable)
{
    ///load the stuff into map from file
}
