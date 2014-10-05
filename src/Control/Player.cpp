#include "Player.hpp"
#include "globals.hpp"

Player::Player(const PlayerData& rData) : Intelligence(rData)
{
    m_inputConfig = rData.keyConfig;
    m_playerMode = rData.playerMode;

    m_camera.setViewportSF(rData.viewport);
    m_camera.toggleRotation();
}
Player::~Player()
{

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
IOBaseReturn Player::input(IOBaseArgs)
{
    if(rCommand == "setState")
    {
        std::string com;
        rInput >> com;
        if(com == "Interfacing")
            setState(PlayerState::Interfacing);
        else if(com == "Playing")
            setState(PlayerState::Playing);
        else if(com == "Editing")
            setState(PlayerState::Editing);
        else
        {
            ///ERROR LOG
            std::cout << "\n[" << com << "] is not a valid playerMode.";
            std::cout << "\n" << FILELINE;
        }
    }
    else
        Intelligence::input(rInput, rCommand);
}
