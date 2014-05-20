#ifndef ActiveEventer_H
#define ActiveEventer_H

#include "Courier.h"

class IOManager;

class ActiveEventer
{
public:
    ActiveEventer();//when we create an Active eventer, we need to pass it an io manager
    virtual ~ActiveEventer();

    void add(std::tr1::shared_ptr<Courier> spCourier);//gets sent a courier and puts it into its vector to be checked later

    void event(const std::string& variable, Event variableName);

protected:
    typedef std::vector<std::tr1::shared_ptr<Courier> > CourierVector;
    std::map<Event, CourierVector> m_spCourierMap;/**holds all the couriers for this object**/
    IOManager* m_pIOManager;//a reference to the world io manager
private:
};

#endif // ActiveEventer_H
