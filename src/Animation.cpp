#include "../include/Animation.hpp"

Animation::Animation():
    _name(""),
    _sprite(),
    _frameCount(1),
    _speed(0),
    _currentFrame(0),
    _repeate(false)
{
   
}

Animation::Animation(const std::string& name, const sf::Texture& texture) :
    Animation(name, texture, 1, 0)
{}

Animation::Animation(const std::string& name, const sf::Texture& texture,
    size_t frameCount, size_t speed) :
    _name(name),
    _sprite(texture),
    _frameCount(frameCount),
    _speed(speed),
    _currentFrame(0),
    _repeate(false)
{
}
void Animation::update() {
    return;
}

const sf::Vector2f& Animation::getSize() const {
    return _size;
}

const std::string& Animation::getName() const {
    return _name;
}

sf::Sprite& Animation::getSprite() {
    return _sprite;
}

bool Animation::hasEnded() const {
    return (_frameCount == 1);
}