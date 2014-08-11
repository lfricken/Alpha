#ifndef METER_H
#define METER_H


class Meter
{
    public:
        Meter();
        virtual ~Meter();

        virtual void setPercentFull(float zeroToOne);

    protected:
    private:
};

#endif // METER_H
