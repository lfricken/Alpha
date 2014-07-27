#ifndef TURRET_H
#define TURRET_H

#include "Chunk.h"
#include "Projectile.h"

struct TurretData
{
    TurretData()
    {
    }

    std::string textureName;
    float fireDelay;
};

class Turret
{
public:
    Turret(const TurretData& rData, GModule* pParent);
    virtual ~Turret();

    virtual void fire(const b2Vec2& coords);

protected:
    std::pair<int, int> m_ammoMagazine;//<current, max>
    std::pair<int, int> m_ammoTotal;//<current, max>

    b2Vec2 m_emitOffset;

    Timer m_reloadTimer;
    Timer m_fireTimer;
private:
};

#endif // TURRET_H
