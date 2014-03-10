#include "Player.h"

Player::Player(int playerNumber)///do something with the number
{
    ///Load pllayer number keys from file
}

Player::~Player()
{
    //dtor
}

Camera& Player::getCamera()
{
    return m_camera;
}
const Camera& Player::getCamera() const
{
    return m_camera;
}

void Player::setPlayerMode(const std::string& mode)
{
    m_playerMode = mode;
}
const std::string& Player::getPlayerMode() const
{
    return m_playerMode;
}

void Player::setInputConfig(const InputConfig& inputConfig)
{
    m_inputConfig = inputConfig;
}
InputConfig& Player::getInputConfig()
{
    return m_inputConfig;
}
const InputConfig& Player::getInputConfig() const
{
    return m_inputConfig;
}
