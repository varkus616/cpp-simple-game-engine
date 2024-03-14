#include "../include/State.hpp"
#include "../include/StateStack.hpp"
#include <iostream>
#include <utility>

State::Context::Context(sf::RenderWindow& window) :
    window(window){}

State::State(StateStack& stack,
    Context context) :
    _context(context),
    _stack(stack){}

State::~State(){}

void State::requestStackPush(States::ID stateID)
{
    _stack.pushState(stateID);
}

void State::requestStackPop()
{
    _stack.popState();
}

void State::requestStateClear()
{
    _stack.clearStates();
}

void State::registerCommand(sf::Keyboard::Key key, const std::string& name)
{
    if (_CommandMap.find(key) != _CommandMap.end())return;
    _CommandMap.insert(std::make_pair(key, name));
}

void State::sendCommand(const Command command)
{
    _CommandQueue.push(command);
}

const std::unordered_map<int, std::string>& State::getCommandMap()const
{
    return _CommandMap;
}

State::Context State::getContext()const
{
    return _context;
}
