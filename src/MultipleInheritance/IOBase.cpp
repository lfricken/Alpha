#include <MultipleInheritance/IOBase.h>
#include <globals.h>

using namespace std;

IOManager& IOBase::m_rIOManager = game.getGameIOManager();

IOBase::IOBase()//unfinished
{
    //ctor
}
IOBase::~IOBase()//unfinished
{
    //dtor
}
IOManager& IOBase::getIOManager()
{
    return m_rIOManager;
}
void IOBase::input(Package package)//unfinished
{
    cout << "\nInput Called on " << m_targetName;
}
void IOBase::setTargetName(string name)//finished
{
    m_targetName = name;
}
string IOBase::getTargetName()//finished
{
    return m_targetName;
}
