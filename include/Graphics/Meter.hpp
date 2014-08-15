#ifndef METER_H
#define METER_H


/**SHOULD THIS EXIST**?

struct MeterData;
class Meter
{
public:
    Meter(const MeterData& rData);
    virtual ~Meter();

    virtual void setPercentFull(float zeroToOne) = 0;
    float getPercentFull() const;

    BaseGraphicsComponent& getBaseGraphicsComponent();
protected:
private:
    float m_currentPercent;//0-1
};

struct MeterData
{
    MeterData()
    {

    }

    std::tr1::shared_ptr<BaseGraphicsComponentData> spDecorDat;

    virtual Meter* generate() const
    {
        std::cout << "\nERROR: " << FILELINE;
        ///ERROR LOG
        //MeterData mutableCopy(*this);
        //return new Meter(mutableCopy);
    }
}**/

#endif // METER_H
