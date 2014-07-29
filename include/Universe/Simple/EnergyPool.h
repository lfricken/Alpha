#ifndef ENERGYPOOL_H
#define ENERGYPOOL_H


class EnergyPool
{
public:
    EnergyPool();
    virtual ~EnergyPool();

    float getEnergy() const;
    void addEnergy(float amount);
    bool consume(float amount);

protected:
private:
    float m_currentEnergy;
    float m_maxEnergy;
};

#endif // ENERGYPOOL_H
