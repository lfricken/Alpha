#ifndef ActiveEventer_H
#define ActiveEventer_H

#include <IO/PassiveEventer.h>
#include <IO/IOManager.h>

class ActiveEventer : public PassiveEventer
{
    public:
        ActiveEventer();//when we create an Active eventer, we need to pass it an io manager
        virtual ~ActiveEventer();

        virtual int amount() const;
        virtual void add(const Courier& courier);//gets sent a courier and puts it into its vector to be checked later
        virtual void event(const std::string variable);/// TEMPLATE/overload me look down //called when a variable would change, so we pass the variable in to see if any of the couriers should be activated
        ///follow http://publib.boulder.ibm.com/infocenter/lnxpcomp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8l.doc%2Flanguage%2Fref%2Foverloading_function_templates.htm

    protected:
        std::vector<Courier> m_courierList;//the list of Couriers held by this eventer (each eventer is specific to a small group, or 1, variables in an entity
        virtual bool f_check(std::string variable, Condition& condition);///TEMPLATE ME! //checks the condition and returns true if it was satisfied (you may want to just do all of this in the event(); func
        static IOManager& m_rIOManager;//a reference to the world io manager
    private:
};

#endif // ActiveEventer_H
