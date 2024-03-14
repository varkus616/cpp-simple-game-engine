#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>
#include <unordered_map>

#include "Command.hpp"
#include "StateIdentifiers.hpp"

class StateStack;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context
    {
        Context(sf::RenderWindow& window);
          
        sf::RenderWindow& window;
    };

    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void render() = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    //virtual bool handleEvent(const sf::Event event) = 0;

    

    void sendCommand(const Command command);

    const std::unordered_map<int, std::string>& getCommandMap()const;

protected:
    void        requestStackPush(States::ID stateID);
    void        requestStackPop();
    void        requestStateClear();
    void registerCommand(sf::Keyboard::Key key, const std::string& name);
    virtual void executeCommands() = 0;

    Context     getContext() const;


    std::queue<Command> _CommandQueue;

private:
    StateStack&  _stack;
    Context      _context;
    std::unordered_map<int, std::string>   _CommandMap;
    

};
