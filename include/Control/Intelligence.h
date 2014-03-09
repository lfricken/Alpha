#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H
#include <MultipleInheritance/IOBase.h>

class Intelligence : public IOBase
{
    public:
        Intelligence();
        virtual ~Intelligence();


        void setTarget();
        void removeControl();


        bool getControlState() const;
        const sf::Vector2f& getAim() const;
    protected:
    private:
        bool m_hasControl;
        sf::Vector2f m_aim;

        Chunk* m_target;///FIX THIS ASAP
        ///Derived* m_target;
};

#endif // INTELLIGENCE_H
