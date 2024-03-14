#include "../include/MenuState.hpp"
#include <iostream>
MenuState::MenuState(StateStack& stack, Context context) :
    State(stack, context),
    _window(context.window),
    _StartButton(sf::Vector2f(60.f,60.f)),
    _OptionsButton(sf::Vector2f(60.f, 60.f)),
    _ExitButton(sf::Vector2f(60.f, 60.f))
{
    _StartButton.onClick = [this](const sf::Event& event, Button& self) 
        {
            std::cout << "Start!";
            //requestStackPop();
            //requestStackPush(States::ID::GameState);
        };


    _StartButton.setPosition(_window.getSize().x / 2 - 20,
                             _window.getSize().y / 2 + 40);

    _StartButton.setColor(sf::Color::Red);

    _OptionsButton.onClick = [this](const sf::Event& event, Button& self)
        {
            //requestStackPop();
            std::cout << "Opcje !" << std::endl;
        };

    _OptionsButton.setPosition(_StartButton.getPosition().x,
                               _StartButton.getPosition().y 
                                - _OptionsButton.getSize().y - 20);

    _OptionsButton.setColor(sf::Color::Green);

    _ExitButton.onClick = [this](const sf::Event& event, Button& self)
        {
            std::cout << "Exit!";
            //requestStackPop();
            //requestStackPush(States::ID::GameState);
        };


    _ExitButton.setPosition(_OptionsButton.getPosition().x,
        _OptionsButton.getPosition().y
        - _ExitButton.getSize().y - 20);

    _ExitButton.setColor(sf::Color::Blue);

    registerCommand(sf::Keyboard::S, "START");
    registerCommand(sf::Keyboard::O, "OPTIONS");
    registerCommand(sf::Keyboard::E, "EXIT");

}

MenuState::~MenuState()
{}

void MenuState::render()
{
    _StartButton.render(_window);
    _OptionsButton.render(_window);
    _ExitButton.render(_window);
}

bool MenuState::update(sf::Time deltaTime)
{
    executeCommands();
    return true;
}

void MenuState::executeCommands()
{
    while (!_CommandQueue.empty())
    {
        Command& c = _CommandQueue.front();
        if (c.type() == "START")
        {
            if(c.name() == "START"){
                std::cout << "START";
                _StartButton.
                    onClick(sf::Event(), _StartButton);
            }
            if(c.name() == "OPTIONS"){
                _OptionsButton.
                    onClick(sf::Event(), _OptionsButton);
            }
            if (c.name() == "EXIT") { _ExitButton.
                onClick(sf::Event(), _ExitButton); }
        }
        _CommandQueue.pop();
    }
}
//bool MenuState::handleEvent(const sf::Event event)
//{
//    return true;
//}