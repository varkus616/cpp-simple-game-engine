#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

//#include <Player.h>
#include "StateIdentifiers.hpp"

#include <memory>

class StateStack;
class Player;
class AssetManager;
class World;
class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context
    {
        Context(sf::RenderWindow& window, AssetManager* manager);
          
        sf::RenderWindow& window;
        AssetManager* manager;
    };

    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void        requestStackPush(States::ID stateID);
    void        requestStackPop();
    void        requestStateClear();

    Context     getContext() const;

private:
    StateStack* _stack;
    Context     _context;
};
