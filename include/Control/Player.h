#ifndef PLAYER_H
#define PLAYER_H

#include "Intelligence.h"
#include "Camera.h"
#include "defaults.h"

struct InputConfig
{
    InputConfig() :
        up(sf::Keyboard::W),
        down(sf::Keyboard::S),
        left(sf::Keyboard::A),
        right(sf::Keyboard::D),
        rollLeft(sf::Keyboard::A),
        rollRight(sf::Keyboard::D),
        special_1(sf::Keyboard::R),
        special_2(sf::Keyboard::F),
        special_3(sf::Keyboard::C),
        special_4(sf::Keyboard::X),
        primary(sf::Mouse::Left),
        secondary(sf::Mouse::Right)
        {}

    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key rollLeft;
    sf::Keyboard::Key rollRight;
    sf::Keyboard::Key special_1;
    sf::Keyboard::Key special_2;
    sf::Keyboard::Key special_3;
    sf::Keyboard::Key special_4;

    sf::Mouse::Button primary;
    sf::Mouse::Button secondary;
};
struct PlayerData : public IntelligenceData
{
    PlayerData() :
        IntelligenceData(),
        keyConfig(),
        playerMode(def::cntrl::defaultPlayerMode),
        cameraPos(def::cntrl::defaultCameraPos),
        cameraSize(def::cntrl::defaultCameraSize),
        initState(static_cast<PlayerState>(def::cntrl::defaultInitState))
    {}
    InputConfig keyConfig;
    std::string playerMode;
    sf::Vector2f cameraPos;
    sf::Vector2f cameraSize;
    PlayerState initState;
};

class Player : public Intelligence
{
public:
    Player();
    Player(const PlayerData& data);
    virtual ~Player();

    Camera& getCamera();
    const Camera& getCamera() const;

    void setMouseCoords(const sf::Vector2i& screenCoords);
    const sf::Vector2i& getMouseCoords() const;

    void setPlayerMode(const std::string& mode);
    const std::string& getPlayerMode() const;

    void setInputConfig(const InputConfig& inputConfig);
    InputConfig& getInputConfig();
    const InputConfig& getInputConfig() const;
protected:
private:
    virtual void f_initialize(const PlayerData& data);

    sf::Vector2i m_mouseCoords;
    Camera m_camera;
    std::string m_playerMode;///STATE INSTEAD??
    InputConfig m_inputConfig;
};

#endif // PLAYER_H
