#include "../../include/gui/Button.hpp"


Button::FuncType Button::defaultFunc = []
(const sf::Event&, Button&)->void {};

Button::Button(sf::Vector2f size) :
    onClick(defaultFunc), _status(Status::None)
{
    _shape.setSize(size);
}

Button::Button(sf::Vector2f size, const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color) : _status(Status::None) {
    _shape.setSize(size);
    setText(text, font, characterSize, color);
}

Button::Button(sf::Vector2f size, const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color, const FuncType& onClickFunction) : _status(Status::None) {
    _shape.setSize(size);
    setText(text, font, characterSize, color);
    onClick = onClickFunction;
}


Button::~Button()
{
}

void Button::render(sf::RenderWindow& window)
{
    window.draw(_shape);
    window.draw(_text);
}

bool Button::processEvent(const sf::Event& event)
{
    return true;
}

void Button::onMouseEntered()
{
}

void Button::onMouseLeft()
{
}
void Button::setPosition(float x, float y) {
    _shape.setPosition(x, y);
    sf::FloatRect textBounds = _text.getLocalBounds();
    _text.setPosition(x + (_shape.getSize().x - textBounds.width) / 2,
        y + (_shape.getSize().y - textBounds.height) / 2);
}

void Button::setText(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color) {
    _text.setString(text);
    _text.setFont(font);
    _text.setCharacterSize(characterSize);
    _text.setFillColor(color);
}

void Button::setColor(sf::Color color) {
    _shape.setFillColor(color);
}

const sf::Vector2f Button::getPosition() const {
    return _shape.getPosition();
}

const sf::Vector2f Button::getSize() const {
    return _shape.getSize();
}
