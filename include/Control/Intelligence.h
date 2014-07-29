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

    PlayerState getState() const;
    void setState(PlayerState newState);

    virtual IOBaseReturn input(IOBaseArgs);

    void setAim(const b2Vec2& newAim);//in world coordinates
    const b2Vec2& getAim() const;//in world coordinates

    const std::string& getTargetName() const;

    Link<Intelligence, Chunk>& getLinker();
protected:
private:
    virtual void f_initialize(const IntelligenceData& data);

    Link<Intelligence, Chunk> m_linker;

    PlayerState m_playerState;//playing, editing, interfacing ect.
    std::string m_targetName;///WHAT IS THIS
    std::vector<std::tr1::shared_ptr<leon::Panel> > m_HUDspElements;
    Chunk* m_pTarget;

    b2Vec2 m_aim;//in world coordinates
};

#endif // INTELLIGENCE_H
