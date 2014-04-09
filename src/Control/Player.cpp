#include "Player.h"

Player::Player() : Intelligence()
{
    PlayerData data;
    f_initialize(data);
}
Player::Player(const PlayerData& data) : Intelligence(static_cast<IntelligenceData>(data))
{
    f_initialize(data);
}
Player::~Player()
{

}
void Player::f_initialize(const PlayerData& data)
{
    m_inputConfig = data.keyConfig;
    m_playerMode = data.playerMode;
    m_camera.getView().setCenter(data.cameraPos);
    m_camera.getView().setSize(data.cameraSize);
}
Camera& Player::getCamera()
{
    return m_camera;
}
const Camera& Player::getCamera() const
{
    return m_camera;
}
void Player::setMouseCoords(const sf::Vector2i& screenCoords)
{
    m_mouseCoords = screenCoords;
}
const sf::Vector2i& Player::getMouseCoords() const
{
    return m_mouseCoords;
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
