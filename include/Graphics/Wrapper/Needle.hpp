#ifndef NEEDLE_HPP
#define NEEDLE_HPP

struct NeedleData
{
    NeedleData():
        gfxCompData(),

        {

        }



    GraphicsComponentData gfxCompData;
}

class Needle : public GraphicsWrapperInterface
{
public:
    Needle();
    virtual ~Needle();

    void changeDesiredPosition(float radiansCCW);//radians CCW
    void setEnabled(bool enabled);

    void setAnimState(AnimationState state);
protected:
    float f_findStopDist();//radians CCW
private:
    float m_5ntVel;//when we are told to adjust left or right, how much
    float m_fixVel;//how quickly do we try and return to default

    float m_maxLimit;
    float m_minLimit;

    Timer m_timer;
    bool m_isEnabled;
    GraphicsComponent* m_pGfxDerived;
};

#endif // NEEDLE_HPP
