#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H
#include <MultipleInheritance/IOBase.h>
#include <Chunk.h>

class Intelligence : public IOBase
{
    public:
        Intelligence();
        virtual ~Intelligence();

        Chunk* getTarget();
        const Chunk* getTarget() const;
        void setTarget(Chunk* target);
        void removeControl();
        bool getControlState() const;

        void setAim(const sf::Vector2f& newAim);
        const sf::Vector2f& getAim() const;
    protected:
    private:

        bool m_hasControl;
        Chunk* m_target;///FIX THIS ASAP
        ///Derived* m_target;

        sf::Vector2f m_aim;
};

#endif // INTELLIGENCE_H
