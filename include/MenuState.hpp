#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
//#include "StateStack.hpp"
#include "Command.hpp"

#include "gui/Button.hpp"

class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);
    virtual ~MenuState();

    void render() override;
    bool update(sf::Time deltaTime) override;
    void executeCommands() override;
    //bool handleEvent(const sf::Event event) override;

private:
    sf::RenderWindow& _window;
    Button            _StartButton;
    Button            _OptionsButton;
    Button            _ExitButton;


};
