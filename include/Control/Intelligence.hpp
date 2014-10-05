#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H

#include "IOBase.hpp"
#include "Chunk.hpp"
#include "defaults.hpp"
#include "Panel.hpp"

struct IntelligenceData : public IOBaseData
{
    IntelligenceData() :
        IOBaseData(),
        targetName(defaults::control::targetName)
    {}
    std::string targetName;
    std::vector<std::tr1::shared_ptr<leon::Panel> > hudSPelements;
};

class Intelligence : public IOBase
{
public:
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
    Link<Intelligence, Chunk> m_linker;

    PlayerState m_playerState;//playing, editing, interfacing ect.
    std::string m_targetName;//this is the name of the thing we will try and link with (if anything)
    std::vector<std::tr1::shared_ptr<leon::Panel> > m_HUDspElements;

    b2Vec2 m_aim;//in world coordinates
};

#endif // INTELLIGENCE_H
