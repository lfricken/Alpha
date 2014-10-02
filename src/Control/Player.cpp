#include "Player.hpp"
#include "globals.hpp"

Player::Player() : Intelligence()
{
    PlayerData data;
    f_initialize(data);
}
Player::Player(const PlayerData& rData) : Intelligence(static_cast<IntelligenceData>(rData))
{
    f_initialize(rData);
}
Player::~Player()
{

}
void Player::f_initialize(const PlayerData& rData)
{
    m_inputConfig = rData.keyConfig;
    m_playerMode = rData.playerMode;

    m_camera.setViewportSF(rData.viewport);
    m_camera.toggleRotation();
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
void Player::setPlayerMode(const PlayerMode& mode)
{
    m_playerMode = mode;
}
const PlayerMode& Player::getPlayerMode() const
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
