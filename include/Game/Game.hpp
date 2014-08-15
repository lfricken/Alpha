#ifndef GAME_H
#define GAME_H


#include "IOBase.hpp"
#include "OverlayManager.hpp"
#include "TextureAllocator.hpp"
#include "Universe.hpp"

class IOManager;
class ControlManager;

class Game// : public IOBase//holds a universe, OverlayManager, and IOManager, and other stuff
{
public:
    Game();
    virtual ~Game();

    enum Status
    {
        Client,
        Server,
        Local,
        Quit,
    };
    //loop over our contents and do stuff
    //void load(stuff);//loads stuff from files, and puts it in the right places, how should we go about this???
    //void setAddresses();//go through our Couriers, find their targets, and set their addresses, so they don't have to search later
    Status run();
    Status local();
    Status client();
    Status server();

    void loadWindow();

    float getTime() const;

    IOManager& getGameIOManager();
    sf::RenderWindow& getGameWindow();
    Universe& getGameUniverse();
    OverlayManager& getGameOverlayManager();
    TextureAllocator& getTextureAllocator();
    AnimationAllocator& getAnimationAllocator();

    sf::Sprite renderSprite_1;///OMG WTF IS THIS
    sf::Sprite renderSprite_2;///

    sf::RenderTexture rendText_1;///OMG WTF IS THIS;
    sf::RenderTexture rendText_2;
    sf::Shader m_blurShader;
    sf::Shader m_vecFieldShader;
    sf::Shader m_shader;///OMG WTF IS THIS

protected:
private:
    void f_load(const std::string& stuff);//told where to get blueprintsData and mapsData, and panelsData


    /**created first**/
    std::tr1::shared_ptr<AnimationAllocator> m_spAnimAlloc;
    std::tr1::shared_ptr<sf::RenderWindow> m_spWindow;///unfortunately TGUI keeps a pointer to this!!
    std::tr1::shared_ptr<IOManager> m_spIOManager;
    std::tr1::shared_ptr<TextureAllocator> m_spTexAlloc;
    std::tr1::shared_ptr<Universe> m_spUniverse;
    /**needs access to previous ones**/
    std::tr1::shared_ptr<OverlayManager> m_spOverlayManager;
    std::tr1::shared_ptr<ControlManager> m_spControlManager;


    sf::Clock m_clock;
    sf::Image m_icon;
    sf::ContextSettings m_settings;
};

#endif // GAME_H







    /**
    DONT NEED IT ANYMORE
    //std::vector<Courier*> m_allCouriers;///this problem is so old we almost forgot about it
    //IN order to avoid IOManager having to search for objects during runtime, it will find them
    //at load time, and give them pointers to the IOBase part of the target, so later, it can just
    // use the pointer and send the message instantly
    //the problem is, what if that object got deleted...
    //that is solved by our friend: shared_ptr
    //by giving the courier a shared_ptr, even though the object was told to be deleted, it wont delete until
    //all shared_ptr's have tried to delete it
    so a deleted object will actually sit in memory, then it will get the message, and destroy itself
    **/
