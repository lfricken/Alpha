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
        rollLeft(sf::Keyboard::Q),
        rollRight(sf::Keyboard::E),
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
        playerMode(def::cntrl::playerMode),
        cameraPos(def::cntrl::cameraPos),
        cameraSize(def::cntrl::cameraSize),
        initState(def::cntrl::playerState)
    {}

    InputConfig keyConfig;
    PlayerMode playerMode;
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

    void setPlayerMode(const PlayerMode& mode);
    const PlayerMode& getPlayerMode() const;

    void setInputConfig(const InputConfig& inputConfig);
    InputConfig& getInputConfig();
    const InputConfig& getInputConfig() const;
protected:
private:
    virtual void f_initialize(const PlayerData& data);

    sf::Vector2i m_mouseCoords;//where is the mouse of us
    Camera m_camera;
    PlayerMode m_playerMode;//god mode or normal mode?
    InputConfig m_inputConfig;//what keys do
};

#endif // PLAYER_H
