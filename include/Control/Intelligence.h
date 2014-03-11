#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H
#include <MultipleInheritance/IOBase.h>
#include <Chunk.h>

class Intelligence : public IOBase
{
    public:
        Intelligence();
        virtual ~Intelligence();

        friend class Chunk;
        Chunk* getTarget() const;
        bool hasTarget() const;
        void linkControl(Chunk* target);
        void breakControl();//called to break the control links

        void setAim(const sf::Vector2f& newAim);
        const sf::Vector2f& getAim() const;

    protected:
    private:
        void f_forgetTarget();//CONTROL
        void f_setTarget(Chunk* target);
        bool m_hasTarget;
        Chunk* m_pTarget;

        sf::Vector2f m_aim;
};

#endif // INTELLIGENCE_H
