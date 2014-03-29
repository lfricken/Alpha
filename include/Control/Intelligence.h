#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H

#include "IOBase.h"
#include "Chunk.h"
#include "defaults.h"

struct IntelligenceData : public IOBaseData
{
    IntelligenceData() :
        IOBaseData(),
        targetName(defaultTargetName)
        {}
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

        bool toggleSending();
        bool toggleSending(bool newState);//changes whether or not we will send commands
        bool isSending() const;

        void setAim(const sf::Vector2f& newAim);
        const sf::Vector2f& getAim() const;

        void setTargetName(const std::string& target);
        const std::string& getTargetName();

    protected:
    private:
        virtual void f_initialize(const IntelligenceData& data);

        friend class Chunk;
        void f_forgetTarget();//CONTROL
        void f_setTarget(Chunk* target);
        bool m_hasTarget;
        bool m_isSending;
        std::string m_targetName;
        Chunk* m_pTarget;

        sf::Vector2f m_aim;
};

#endif // INTELLIGENCE_H
