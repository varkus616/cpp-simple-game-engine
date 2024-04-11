#include "../include/StateStack.hpp"
#include <cassert>
#include <iostream>

StateStack::StateStack(State::Context context) :
    _Context(context){}

void StateStack::update(sf::Time deltaTime)
{
    for (auto itr = _Stack.rbegin(); itr != _Stack.rend(); ++itr)
    {
        if (!(*itr)->update(deltaTime))
            break;
    }
    applyPendingChanges();
}

void StateStack::render()
{
    for (auto& state : _Stack)
        state->render();
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = _Stack.rbegin(); itr != _Stack.rend(); ++itr)
    {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if ((*itr)->getKeyboardCommandMap().find(event.key.code) == (*itr)->getKeyboardCommandMap().end()) continue;
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
            
            (*itr)->sendCommand(Command((*itr)->getKeyboardCommandMap().at(event.key.code), actionType));
        }
        else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            if ((*itr)->getMouseCommandMap().find(event.key.code) == (*itr)->getMouseCommandMap().end()) continue;
            const std::string actionType = (event.type == sf::Event::MouseButtonPressed) ? "START" : "END";

            (*itr)->sendCommand(Command((*itr)->getMouseCommandMap().at(event.key.code), actionType));
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if ((*itr)->getMouseCommandMap().find(sf::Event::MouseMoved) == (*itr)->getMouseCommandMap().end()) continue;
            const std::string actionType = "CONTINUSE";

            (*itr)->sendCommand(Command((*itr)->getMouseCommandMap().at(sf::Event::MouseMoved), actionType));
        }
        
    }
    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
    _PendingList.push_back(PendingChange(StackAction::Push,
        stateID));
}

void StateStack::popState()
{
    _PendingList.push_back(PendingChange(StackAction::Pop));
}

void StateStack::clearStates()
{
    _PendingList.push_back(PendingChange(StackAction::Clear));
}

bool StateStack::isEmpty() const
{
    return _Stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = _Factories.find(stateID);
    assert(found != _Factories.end() && "Error: State can't be created. Register state before creating it.");
    return found->second();
}



void StateStack::applyPendingChanges()
{
    for (auto& change : _PendingList)
    {
        switch (change.stAction)
        {
        case Push:
            _Stack.push_back(createState(change.stateID));
            break;

        case Pop:
            _Stack.pop_back();
            break;

        case Clear:
            _Stack.clear();
            break;
        }
    }
    _PendingList.clear();
}
StateStack::PendingChange::PendingChange(StackAction stAction,
    States::ID stateID) :
    stAction(stAction),
    stateID(stateID)
{

}