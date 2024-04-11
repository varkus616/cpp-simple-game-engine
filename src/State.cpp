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

void State::registerKeyboardCommand(int key, const std::string& name)
{
    if (_KeyboardCommandMap.find(key) != _KeyboardCommandMap.end())return;
    _KeyboardCommandMap.insert(std::make_pair(key, name));
}

void State::registerMouseCommand(int key, const std::string& name)
{
    if (_MouseCommandMap.find(key) != _MouseCommandMap.end())return;
    _MouseCommandMap.insert(std::make_pair(key, name));
}

void State::sendCommand(const Command command)
{
    _CommandQueue.push(command);
}

const std::unordered_map<int, std::string>& State::getKeyboardCommandMap()const
{
    return _KeyboardCommandMap;
}


const std::unordered_map<int, std::string>& State::getMouseCommandMap()const
{
    return _MouseCommandMap;
}


State::Context State::getContext()const
{
    return _context;
}
