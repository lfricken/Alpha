#ifndef IOBASE_H
#define IOBASE_H

#include "stdafx.h"
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
class PassiveEventer;

#define IOBaseReturn void
#define IOBaseArgs sf::Packet& rInput

struct IOBaseData
{
    IOBaseData () {}
    IOBaseData (ClassType s1, const std::string& s2) : type(s1), name(s2) {}
    ClassType type;
    std::string name;
    std::vector<std::tr1::shared_ptr<Courier> > spCourierList;
};
class IOBase//base class inherited by literally everything, that way objects can always communicate
{
public:
    IOBase();
    IOBase(const IOBaseData& data);
    virtual ~IOBase();


    void addCouriers(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList);
    std::tr1::shared_ptr<PassiveEventer> getEventer();

    virtual IOManager& getIOManager();
    void setName(const std::string& name);//sets the name of this entity
    const std::string& getName() const;//gets the name of this entity
    unsigned int getID() const;//gets the name of this entity
    ClassType getType() const;


    virtual int damage(int damage);
    virtual int getHealth() const;
    virtual IOBaseReturn input_1(IOBaseArgs);
    virtual IOBaseReturn input_2(IOBaseArgs);
    virtual IOBaseReturn input_3(IOBaseArgs);
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
    friend class Universe;
    void f_setID(unsigned int newID);//sets the name of this entity
    void f_initialize(const IOBaseData& data);

    ClassType m_type;//type of object that we are
    std::string m_name;//used by IO manager to locate specific named objects
    unsigned int m_ID;

    std::tr1::shared_ptr<PassiveEventer> m_spEventer;
    IOManager& m_rIOManager;
private:
};

#endif // IOBASE_H
