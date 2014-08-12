#ifndef METER_H
#define METER_H


class Meter
{
    public:
        Meter();
        virtual ~Meter();

        virtual void setPercentFull(float zeroToOne) = 0;

    protected:
    private:
        float m_currentPercent;//0-1
};

#endif // METER_H
