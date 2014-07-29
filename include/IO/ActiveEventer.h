#ifndef ActiveEventer_H
#define ActiveEventer_H

#include "Courier.h"

class IOManager;

typedef std::vector<std::tr1::shared_ptr<Courier> > CourierVector;

class ActiveEventer
{
public:
    ActiveEventer();//when we create an Active eventer, we need to pass it an io manager
    virtual ~ActiveEventer();

    void add(const Courier& rCourier);//gets sent a courier and puts it into its vector to be checked later
    void addList(const std::vector<Courier>& rCourierList);
    void event(const std::string& variable, Event variableName);

    std::map<Event, CourierVector>& getCourierMap();

protected:
private:
    std::map<Event, CourierVector> m_spCourierMap;/**holds all the couriers for this object**/
};

#endif // ActiveEventer_H
