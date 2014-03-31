#ifndef IOBASE_H
#define IOBASE_H

#include "stdafx.h"
#include "defaults.h"
#include "ActiveEventer.h"
#include "Types.h"

/*HOW IO WORKS
When some event happens, whether its a player pressing a button, or a condition being met, a signal needs to sent to the target to tell it what to do.
All messages, regardless of their origin are sent to IOManager, so any object that wants to ever send a message needs to know about the IOManager. IOManager needs to know
about Universe and OverlayManager, so it can make things happen in them, and then objects inside of OverlayManager and Universe need to know about IOManager for reasons we just talked about.
In addition, Universe and OverlayManager need to have the input function so buttons and world events can call functions directly on eachother.
*/

class IOManager;
class IOBase;
struct Courier;
class ActiveEventer;

#define IOBaseReturn void
#define IOBaseArgs sf::Packet& rInput

struct IOBaseData//initialized
{
    IOBaseData () :
        type(defaultClassType),
        isEnabled(defaultIsEnabled),
        name(defaultName),
        ID(defaultID)
        {}
    ClassType type;
    bool isEnabled;
    std::string name;
    unsigned int ID;

    std::vector<std::tr1::shared_ptr<Courier> > spCourierList;
};
class IOBase//base class inherited by literally everything, that way objects can always communicate
{
public:
    IOBase();
    IOBase(const IOBaseData& data);
    virtual ~IOBase();


    void addCouriers(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList);
    std::tr1::shared_ptr<ActiveEventer> getEventer();

    virtual void resetEventer();
    virtual IOManager& getIOManager();
    void setName(const std::string& name);//sets the name of this entity
    const std::string& getName() const;//gets the name of this entity
    unsigned int getID() const;//gets the name of this entity
    ClassType getType() const;

    virtual int getHealth() const;
    virtual IOBaseReturn input_1(IOBaseArgs);/**ENABLE**////where should these be named??
    virtual IOBaseReturn input_2(IOBaseArgs);/**DISABLE**/
    virtual IOBaseReturn input_3(IOBaseArgs);/**DIE**/
    virtual IOBaseReturn input_4(IOBaseArgs);
    virtual IOBaseReturn input_5(IOBaseArgs);
    virtual IOBaseReturn input_6(IOBaseArgs);
    virtual IOBaseReturn input_7(IOBaseArgs);
    virtual IOBaseReturn input_8(IOBaseArgs);
    virtual IOBaseReturn input_9(IOBaseArgs);
    virtual IOBaseReturn input_10(IOBaseArgs);
    virtual IOBaseReturn input_11(IOBaseArgs);
    virtual IOBaseReturn input_12(IOBaseArgs);
    virtual IOBaseReturn input_13(IOBaseArgs);
    virtual IOBaseReturn input_14(IOBaseArgs);
    virtual IOBaseReturn input_15(IOBaseArgs);
    virtual IOBaseReturn input_16(IOBaseArgs);
    virtual IOBaseReturn input_17(IOBaseArgs);
    virtual IOBaseReturn input_18(IOBaseArgs);
    virtual IOBaseReturn input_19(IOBaseArgs);
    virtual IOBaseReturn input_20(IOBaseArgs);

protected:
    friend class Universe;//to set id's
    void f_setID(unsigned int newID);//sets the name of this entity

    ClassType m_type;//type of object that we are
    bool m_isEnabled;
    std::string m_name;//used by IO manager to locate specific named objects
    unsigned int m_ID;

    std::tr1::shared_ptr<ActiveEventer> m_spEventer;
    IOManager& m_rIOManager;
private:
    virtual void f_initialize(const IOBaseData& data);
};

#endif // IOBASE_H
