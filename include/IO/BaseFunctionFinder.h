#ifndef BASEFUNCTIONFINDER_H
#define BASEFUNCTIONFINDER_H

#include "stdafx.h"
#include "defaults.h"
class IOBase;

typedef IOBaseReturn (IOBase::*TargetFunc)(IOBaseArgs);//this look weird, but it defines TargetFunc, to be a function pointer that returns IOBaseReturn, and takes IOBaseArgs

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
