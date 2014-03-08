#ifndef GAME_H
#define GAME_H

#include <IO/IOManager.h>
#include <TextureAllocator.h>
#include <ControlManager.h>

class Game : public IOBase//holds a universe, OverlayManager, and IOManager, and other stuff
{
public:
    Game();
    virtual ~Game();

    enum Status
    {
        Client,
        Server,
        Local,
        Quit
    };
    //loop over our contents and do stuff
    //void load(stuff);//loads stuff from files, and puts it in the right places, how should we go about this???
    //void setAddresses();//go through our Couriers, find their targets, and set their addresses, so they don't have to search later
    Status run();
    Status local();
    Status client();
    Status server();

    IOManager& getGameIOManager();
    sf::RenderWindow& getGameWindow();
    Universe& getGameUniverse();
    OverlayManager& getGameOverlayManager();
    TextureAllocator& getTextureAllocator();


protected:
private:
    std::tr1::shared_ptr<IOManager> m_spGameIOManager;//the games IOManager
    OverlayManager m_gameOverlayManager;
    std::tr1::shared_ptr<sf::RenderWindow> m_spGameWindow;//the display window
    TextureAllocator m_texAlloc;
    Universe m_gameUniverse;
    std::tr1::shared_ptr<ControlManager> m_spGameControlManager;

    sf::ContextSettings m_settings;///how can we edit the settings of the window?
    sf::Image m_icon;

    void f_load(std::string stuff);
    std::vector<Courier*> m_allCouriers;///this problem is so old we almost forgot about it
    ///IN order to avoid IOManager having to search for objects during runtime, it will find them
    ///at load time, and give them pointers to the IOBase part of the target, so later, it can just
    /// use the pointer and send the message instantly
    ///the problem is, what if that object got deleted...
    ///that is solved by our friend: shared_ptr
    ///by giving the courier a shared_ptr, even though the object was told to be deleted, it wont delete until
    ///all shared_ptr's have tried to delete it
    ///so a deleted object will actually sit in memory, then it will get the message, and destroy itself
};

#endif // GAME_H
