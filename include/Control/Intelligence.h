#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H

#include "IOBase.h"
#include "Chunk.h"

struct IntelligenceData
{
    IOBaseData baseData;
    std::string targetName;
};

class Intelligence : public IOBase
{
    public:
        Intelligence();
        Intelligence(const IntelligenceData& data);
        virtual ~Intelligence();

        Chunk* getTarget() const;
        bool hasTarget() const;
        void linkControl(Chunk* target);
        void breakControl();//called to break the control links

        void setAim(const sf::Vector2f& newAim);
        const sf::Vector2f& getAim() const;

        void setTargetName(const std::string& target);
        const std::string& getTargetName();

    protected:
    private:
        friend class Chunk;
        void f_forgetTarget();//CONTROL
        void f_setTarget(Chunk* target);
        bool m_hasTarget;
        std::string m_targetName;
        Chunk* m_pTarget;

        sf::Vector2f m_aim;
};

#endif // INTELLIGENCE_H
