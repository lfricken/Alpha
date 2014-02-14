#ifndef IOBASE_H
#define IOBASE_H

#include <stdafx.h>


/*HOW IO WORKS
When some event happens, whether its a player presssing a button, or a condition being met, a signal needs to sent to the target to tell it what to do.
All messages, regardless of their origin are sent to IOManager, so any object that wants to ever send a message needs to know about the IOManager. IOManager needs to know
about Universe and OverlayManager, so it can make things happen in them, and then objects inside of OverlayManager and Universe need to know about IOManager for reasons we just talked about.
In addition, Universe and OverlayManager need to have the input function so buttons and world events can call functions directly on eachother.
*/

/*HOW DO WE PROPERLY DO INCLUDE HIERARCHIES???
???????????????????????????????????????????????????????
*/

/*DONT USE NAMESPACES IN HEADERS???
*/
class IOManager;
class IOBase;

//when outside of the eventer, pass these around by value, it has to do with the fact that they might get destroyed so they cant be addressed!:
struct Condition//used to determine if the package should be sent
{
    std::string value;//the value to compare to the current variable
    char comparison;//character type used to compare, so it could be >, <, or =
    bool repeatable;//used by the Eventer to decide whether to keep this Courier after it got activated once
};

struct Package//the thing that is sent to IO manager and ultimately tells some entity what to do
{
    std::tr1::shared_ptr<IOBase> spTargetAddress;///a pointer that points to the target, so that IOmanager can immediately do it
    std::string targetName;//the name of the target
    std::string command;//the action the target should take
    std::string parameter;//addition information used to do the action, such as set health to the parameter
    float delay;//delay used by IO manager, to wait that many seconds to send it to the target
};
struct Courier//just used to couple a Condition to its Package
{
    Condition condition;
    Package package;
};


class IOBase//base class inherited by literally everything, that way objects can always communicate
{
    public:
        IOBase();
        virtual ~IOBase();

        virtual IOManager& getIOManager();

        virtual void input(Package package);//called by IO manager when this entity is being sent a message

        virtual void setTargetName(std::string name);//sets the name of this entity
        virtual std::string getTargetName();//gets the name of this entity
    protected:
        std::string m_targetName;//used by IO manager to locate specific named objects
        static IOManager& m_rIOManager;
    private:
};

#endif // IOBASE_H
