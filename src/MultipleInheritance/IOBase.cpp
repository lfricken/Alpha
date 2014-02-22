#include <MultipleInheritance/IOBase.h>
#include <globals.h>

using namespace std;

IOManager& IOBase::m_rIOManager = game.getGameIOManager();

IOBase::IOBase()//unfinished
{
}
IOBase::~IOBase()//unfinished
{
}
IOManager& IOBase::getIOManager()
{
    return m_rIOManager;
}
bool IOBase::input(Package& rPackage)//unfinished
{
    if(rPackage.commandType == CORE)
        return coreInput(rPackage);
    else if(rPackage.commandType == SPECIAL)
        return specialInput(rPackage);
    else
        return false;
}
void IOBase::setTargetName(string name)//finished
{
    m_targetName = name;
}
const string& IOBase::getTargetName() const//finished
{
    return m_targetName;
}
void IOBase::damage(int damage)
{
}
bool IOBase::coreInput(Package& rPackage)
{
    if(rPackage.command == "Damage")
    {
        damage(atof(rPackage.parameter.c_str()));
        return true;
    }
    else if(rPackage.command == "Activate1")
    {
        return false;
        ///not done with that stuff yet
    }
    else
        return false;
}
bool IOBase::specialInput(Package& rPackage)
{
    return false;
}
