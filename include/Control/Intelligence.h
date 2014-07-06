#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H

#include "IOBase.h"
#include "Chunk.h"
#include "defaults.h"
#include "Panel.h"

struct IntelligenceData : public IOBaseData
{
    IntelligenceData() :
        IOBaseData(),
        targetName(def::cntrl::targetName)
    {}
    std::string targetName;
    std::vector<std::tr1::shared_ptr<leon::Panel> > hudSPelements;
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

    PlayerState getState() const;
    void setState(PlayerState newState);

    virtual IOBaseReturn input(IOBaseArgs);

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
    PlayerState m_playerState;//playing, editing, interfacing ect.
    std::string m_targetName;
    std::vector<std::tr1::shared_ptr<leon::Panel> > m_HUDspElements;
    Chunk* m_pTarget;

    sf::Vector2f m_aim;
};

#endif // INTELLIGENCE_H
