#ifndef BASEFUNCTIONFINDER_H
#define BASEFUNCTIONFINDER_H

#include "stdafx.h"
class IOBase;

typedef void (IOBase::*TargetFunc)(sf::Packet& input);
class BaseFunctionFinder
{
    public:
        BaseFunctionFinder();
        virtual ~BaseFunctionFinder();

        TargetFunc getFunction(const std::string& alias);
        void load(const std::string& aliasTable);
    private:
        std::map<std::string, TargetFunc> m_aliasMap;
};

#endif // BASEFUNCTIONFINDER_H
