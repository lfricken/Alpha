#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "stdafx.hpp"

#include "AnimationAllocator.hpp"
#include "AnimationSetting.hpp"
#include "Timer.hpp"


/**used by GraphicsBase to control animation state**/
//has a state, which controls what sequence animLoop should be using
//and has an offset to control where on the texture the looping is happening (as opposed to just 0,0 origin)
class AnimationController
{
public:
    AnimationController();
    virtual ~AnimationController();

    void load(const std::string& animationFile);//these are used to control what the various animation states should do

    void setState(const AnimationState& state);
    void restart();//starts from beginning
    const sf::Vector2f& getTile();//get the current tile we should be on
    const sf::Vector2f& getTexTileSize() const;

protected:
private:
    void f_update();//figure out the correct tile we should be displaying right now, and the other data

    const AnimSet* m_pSettingsList;//pointer we hold that points at an animation set that AnimationAllocator holds

    int m_currentIndex;
    const AnimationSetting* m_pCurrentSetting;//a sequence of tile coordinates to loop through


    Timer m_timer;
    float m_accumulatedTime;//stores residual time left over from a switch, like 0.01 seconds.
};

#endif // ANIMATIONCONTROLLER_H
