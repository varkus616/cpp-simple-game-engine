#pragma once
#include "../include/State.hpp"
#include "../include/StateIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


class StateStack : private sf::NonCopyable
{
public:
    enum StackAction
    {
        Push,
        Pop,
        Clear
    };
    explicit StateStack(State::Context context);

    template<typename T>
    void     registerState(States::ID stateID);

    void     update(sf::Time deltaTime);
    void     draw();
    void     handleEvent(const sf::Event& event);

    void     pushState(States::ID stateID);
    void     popState();
    void     clearStates();

    bool     isEmpty() const;

private:
    State::Ptr  createState(States::ID stateID);
    void        applyPendingChanges();

    struct PendingChange
    {
        explicit PendingChange(StackAction stAction,
            States::ID stateID = States::None);
        StackAction stAction;
        States::ID  stateID;
    };

private:
    std::vector<State::Ptr>         _Stack;
    std::vector<PendingChange>      _PendingList;

    State::Context                  _Context;
    std::map<States::ID,
        std::function<State::Ptr()>>    _Factories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
    _Factories[stateID] = [this]()
        {
            return State::Ptr(new T(*this, _Context));
        };
}