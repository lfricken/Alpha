#include "Player.h"


Player::~Player()
{

}
Player::Player(const PlayerData& data) : Intelligence(data.intellData)
{
    m_inputConfig = data.keyConfig;
    m_playerMode = data.playerMode;
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
