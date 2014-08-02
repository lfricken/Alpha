#include "AnimationController.hpp"

AnimationController::AnimationController()
{
    ///m_animLoop.setDelay(0.0167);


    ///LOAD THESE FROM A FILE SPECIFIC TO THE TEXTURE

        setState(AnimationState::Default);
}
AnimationController::~AnimationController()
{

}
void AnimationController::load(const std::string& animationFile)
{
    m_default.push_back(sf::Vector2f(0, 0));

    m_damaged.push_back(sf::Vector2f(1, 0));

    m_activated.push_back(sf::Vector2f(0, 0));
    m_activated.push_back(sf::Vector2f(1, 0));
    m_activated.push_back(sf::Vector2f(2, 0));
    m_activated.push_back(sf::Vector2f(3, 0));

    m_destroyed.push_back(sf::Vector2f(2, 0));
    m_destroyed.push_back(sf::Vector2f(3, 0));
    /*
        m_destroyed.push_back(sf::Vector2f(0, 0));
        m_destroyed.push_back(sf::Vector2f(1, 0));
        m_destroyed.push_back(sf::Vector2f(2, 0));
        m_destroyed.push_back(sf::Vector2f(3, 0));
        m_destroyed.push_back(sf::Vector2f(4, 0));
        m_destroyed.push_back(sf::Vector2f(5, 0));
        m_destroyed.push_back(sf::Vector2f(6, 0));
        m_destroyed.push_back(sf::Vector2f(7, 0));

        m_destroyed.push_back(sf::Vector2f(0, 1));
        m_destroyed.push_back(sf::Vector2f(1, 1));
        m_destroyed.push_back(sf::Vector2f(2, 1));
        m_destroyed.push_back(sf::Vector2f(3, 1));
        m_destroyed.push_back(sf::Vector2f(4, 1));
        m_destroyed.push_back(sf::Vector2f(5, 1));
        m_destroyed.push_back(sf::Vector2f(6, 1));
        m_destroyed.push_back(sf::Vector2f(7, 1));

        m_destroyed.push_back(sf::Vector2f(0, 2));
        m_destroyed.push_back(sf::Vector2f(1, 2));
        m_destroyed.push_back(sf::Vector2f(2, 2));
        m_destroyed.push_back(sf::Vector2f(3, 2));
        m_destroyed.push_back(sf::Vector2f(4, 2));
        m_destroyed.push_back(sf::Vector2f(5, 2));
        m_destroyed.push_back(sf::Vector2f(6, 2));
        m_destroyed.push_back(sf::Vector2f(7, 2));

        m_destroyed.push_back(sf::Vector2f(0, 3));
        m_destroyed.push_back(sf::Vector2f(1, 3));
        m_destroyed.push_back(sf::Vector2f(2, 3));
        m_destroyed.push_back(sf::Vector2f(3, 3));
        m_destroyed.push_back(sf::Vector2f(4, 3));
        m_destroyed.push_back(sf::Vector2f(5, 3));
        m_destroyed.push_back(sf::Vector2f(6, 3));
        m_destroyed.push_back(sf::Vector2f(7, 3));

        m_destroyed.push_back(sf::Vector2f(0, 4));
        m_destroyed.push_back(sf::Vector2f(1, 4));
        m_destroyed.push_back(sf::Vector2f(2, 4));
        m_destroyed.push_back(sf::Vector2f(3, 4));
        m_destroyed.push_back(sf::Vector2f(4, 4));
        m_destroyed.push_back(sf::Vector2f(5, 4));
        m_destroyed.push_back(sf::Vector2f(6, 4));
        m_destroyed.push_back(sf::Vector2f(7, 4));

        m_destroyed.push_back(sf::Vector2f(0, 5));
        m_destroyed.push_back(sf::Vector2f(1, 5));
        m_destroyed.push_back(sf::Vector2f(2, 5));
        m_destroyed.push_back(sf::Vector2f(3, 5));
        m_destroyed.push_back(sf::Vector2f(4, 5));
        m_destroyed.push_back(sf::Vector2f(5, 5));
        m_destroyed.push_back(sf::Vector2f(6, 5));
        m_destroyed.push_back(sf::Vector2f(7, 5));
        */
}
const sf::Vector2f& AnimationController::getTile()
{
    return m_animLoop.getTile();
}
void AnimationController::setState(AnimationState stat)
{
    ///to avoid case break
    /**access [stat] index of list of States, and do
        m_animLoop.setSequence(get<thing0>());
        m_animLoop.runOnce(get<thing1>());
        m_animLoop.setDelay(get<thing2>());
        m_animLoop.restart();**/
        ///load this stuff from file

    ///but for now:
    switch (stat)
    {
    case AnimationState::Default:
        m_animLoop.setSequence(m_default);
        m_animLoop.runOnce(false);
        m_animLoop.setDelay(100);
        m_animLoop.restart();
        break;
    case AnimationState::Activated:
        m_animLoop.setSequence(m_activated);
        m_animLoop.runOnce(false);
        m_animLoop.setDelay(0.25);
        m_animLoop.restart();
        break;
    case AnimationState::Enabled:

        break;
    case AnimationState::Disabled:

        break;
    case AnimationState::Damaged:
        m_animLoop.setSequence(m_damaged);
        m_animLoop.runOnce(false);
        m_animLoop.setDelay(0.5);
        m_animLoop.restart();
        break;
    case AnimationState::Destroyed:
        ///all of these attributes should be for each
        m_animLoop.setSequence(m_destroyed);
        m_animLoop.runOnce(true);
        m_animLoop.setDelay(0.5);
        m_animLoop.restart();
        break;
    default:

        break;
    }
}
