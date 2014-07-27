#ifndef IOBASE_H
#define IOBASE_H

#include "stdafx.h"
#include "defaults.h"
#include "ActiveEventer.h"

#include "ClassType.h"
#include "Attributes.h"

#include "IOComponent.h"

/*HOW IO WORKS
When some event happens, whether its a player pressing a button, or a condition being met, a signal needs to sent to the target to tell it what to do.
All messages, regardless of their origin are sent to IOManager, so any object that wants to ever send a message needs to know about the IOManager. IOManager needs to know
about Universe and OverlayManager, so it can make things happen in them, and then objects inside of OverlayManager and Universe need to know about IOManager for reasons we just talked about.
In addition, Universe and OverlayManager need to have the input function so buttons and world events can call functions directly on eachother.
*/

class IOManager;
struct Courier;

struct IOBaseData//initialized
{
    IOBaseData () :
        type(def::io::classType),
        isEnabled(def::io::isEnabled),
        name(def::io::name)/**ID is calculated with a name**/
        //  , ID(defaultID) old
    {
        butes.setBute(Butes::isSolid, false);
        butes.setBute(Butes::isDestructable, false);
    }
    // unsigned long long int getID() const{return ID;} old

    ClassType type;
    Attributes butes;
    bool isEnabled;
    std::string name;

    std::vector<std::tr1::shared_ptr<Courier> > spCourierList;///THIS SHOULD NOT BE HOLDING POINTERS
};
class IOBase//base class inherited by literally everything, that way objects can always communicate
{
public:
    IOBase();
    IOBase(const IOBaseData& data);
    virtual ~IOBase();

    /**GENERIC**/
    const IOComponent& getIOComponent() const;
    unsigned int getID() const;
    const std::string& getName() const;
    ClassType getType() const;
    const Attributes& getButes() const;

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
    virtual void enable();
    virtual void disable();
    virtual void trigger();

protected:
    void f_varEvent(std::string value, Event eventType);//takes a generic variable type, and sends the data to eventer
    void f_varEvent(int value, Event eventType);
    void f_varEvent(float value, Event eventType);
    void f_varEvent(double value, Event eventType);

    IOComponent* m_pIOComponent;
    IOManager& m_rIOManager;

    ClassType m_type;//type of object that we are
    Attributes m_attributes;

    bool m_isEnabled;
private:
    virtual void f_initialize(const IOBaseData& data);
};

#endif // IOBASE_H
