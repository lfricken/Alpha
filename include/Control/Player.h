#ifndef PLAYER_H
#define PLAYER_H
#include <Intelligence.h>
#include <Camera.h>

struct InputConfig
{
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


class Player : public Intelligence
{
public:
    Player(int playerNumber);
    virtual ~Player();

    Camera& getCamera();
    const Camera& getCamera() const;

    void setPlayerMode(const std::string& mode);
    const std::string& getPlayerMode() const;

    void setInputConfig(const InputConfig& inputConfig);
    InputConfig& getInputConfig();
    const InputConfig& getInputConfig() const;
protected:
private:
    Camera m_camera;
    std::string m_playerMode;///STATE INSTEAD??
    InputConfig m_inputConfig;
};

#endif // PLAYER_H
