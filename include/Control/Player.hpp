#ifndef PLAYER_H
#define PLAYER_H

#include "Intelligence.hpp"
#include "Camera.hpp"
#include "defaults.hpp"

struct InputConfig
{
    InputConfig() :
        up(sf::Keyboard::W),
        down(sf::Keyboard::S),
        left(sf::Keyboard::Q),
        right(sf::Keyboard::E),
        rollLeft(sf::Keyboard::A),
        rollRight(sf::Keyboard::D),
        special_1(sf::Keyboard::Space),
        special_2(sf::Keyboard::F),
        special_3(sf::Keyboard::C),
        special_4(sf::Keyboard::R),
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
        playerMode(defaults::control::playerMode),
        cameraPos(0, 0),
        initState(defaults::control::playerState),
        viewport(0,0,1,1)
    {}

    InputConfig keyConfig;
    PlayerMode playerMode;
    b2Vec2 cameraPos;
    PlayerState initState;
    sf::FloatRect viewport;
};

class Player : public Intelligence
{
public:
    Player();
    Player(const PlayerData& rData);
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
    virtual void f_initialize(const PlayerData& rData);

    sf::Vector2i m_mouseCoords;//where is our mouse on the screen
    Camera m_camera;
    PlayerMode m_playerMode;//god mode or normal mode?
    InputConfig m_inputConfig;//controls what the keys do
};

#endif // PLAYER_H
