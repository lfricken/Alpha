#ifndef ANIMATIONALLOCATOR_H
#define ANIMATIONALLOCATOR_H

#include "AnimationSetting.hpp"
typedef std::map<AnimationState, AnimationSetting> AnimSet;//a set of animation settings



class AnimationAllocator
{
public:
    AnimationAllocator();
    virtual ~AnimationAllocator();

    const AnimSet* requestPtr(const std::string& rFileName);
protected:
private:

    std::map<std::string, std::tr1::shared_ptr<AnimSet> > m_animationSets;
};

#endif // ANIMATIONALLOCATOR_H
