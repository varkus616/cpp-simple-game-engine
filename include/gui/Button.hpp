#pragma once

#include <functional>
#include <SFML/Graphics.hpp>


class Button
{
public:
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    using FuncType = std::function<void(const sf::Event& event, Button& self)>;
    static FuncType defaultFunc;

    bool processEvent(const sf::Event& event);

    void setPosition(float x, float y);

    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color = sf::Color::White);

    const sf::Vector2f getPosition()const;

    const sf::Vector2f getSize()const;

    void setColor(sf::Color color);

    void render(sf::RenderWindow& window);


    Button(sf::Vector2f size);

    Button(sf::Vector2f size,
        const std::string& text,
        const sf::Font& font,
        unsigned int characterSize,
        const sf::Color& color);

    Button(sf::Vector2f size,
        const std::string& text,
        const sf::Font& font,
        unsigned int characterSize,
        const sf::Color& color,
        const FuncType& onClickFunction);

    virtual ~Button();

    FuncType onClick;

protected:
    

    virtual void onMouseEntered();
    virtual void onMouseLeft();

private:
    sf::RectangleShape _shape; 
    sf::Text _text;
    enum Status {
        None = 0,
        Hover
    };
    int _status;
};
