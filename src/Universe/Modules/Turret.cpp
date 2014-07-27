#include "Turret.h"

#include "Angles.h"

Turret::Turret() : GModule()
{
    TurretData data;
    f_initialize(data);
}
Turret::Turret(const TurretData& rData) : GModule(static_cast<GModuleData>(rData))
{
    f_initialize(rData);
}
Turret::~Turret()
{

}
void Turret::f_initialize(const TurretData& rData)
{
    m_ammoContainer = rData.ammo;
    m_refireTimer.setCountDown(rData.refireDelay);
    m_canPivot = rData.canPivot;
    m_spTurretTop.reset(new Decoration(rData.decorationData));
    m_fireCommands = rData.fireCommandList;

    std::vector<TurretBarrelData> data = rData.barrelData;
    for(auto it = data.begin(); it != data.end(); ++it)
    {
        it->pParent = this;
        m_barrels.push_back(TurretBarrel(*it));
    }
}
void Turret::primary(const b2Vec2& coords)
{
    if(m_refireTimer.isTimeUp() && (!m_ammoContainer.isReloading()))
    {
        queueCommands();
    }
}
void Turret::secondary(const b2Vec2& coords)
{
    if(m_refireTimer.isTimeUp() && (!m_ammoContainer.isReloading()))
    {
        queueCommands();
    }
}
void Turret::aim(const b2Vec2& coords)
{
    b2Vec2 difference(coords - getCenter());
    if(difference.x >= 0)
        m_aimAngle = atan(difference.y/difference.x);
    else
        m_aimAngle = pi+atan(difference.y/difference.x);
}
float Turret::getAimAngle() const
{
    return m_aimAngle;
}
void Turret::queueCommands()
{
    m_queuedCommands = m_fireCommands;
}
bool Turret::physUpdate()
{
    //update us to aim at the correct angle before trying to fire anything

    b2Vec2 position(getCenter());

    m_spTurretTop->setPosition(position);
    m_spTurretTop->setRotation(leon::radToDeg(m_aimAngle));

    for(auto it = m_barrels.begin(); it != m_barrels.end(); ++it)
        it->update(position, m_aimAngle);




    //and then check if we should fire any of our barrels
    for(unsigned int i = 0; i<m_queuedCommands.size(); ++i)
    {
        m_queuedCommands[i].delay -= m_commandTimer.getTimeElapsed();
        if(m_queuedCommands[i].delay <= 0)
        {
            m_barrels[m_queuedCommands[i].barrelIndex].fire();
            m_queuedCommands.erase(m_queuedCommands.begin() + i);
            --i;
        }
    }
}
