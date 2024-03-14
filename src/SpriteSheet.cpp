#include "../include/SpriteSheet.hpp"

SpriteSheet::SpriteSheet(sf::Texture& texture, int spriteWidth, int spriteHeight) :
    _texture(texture),
    _frameWidth(spriteWidth),
    _frameHeight(spriteHeight)
{

    int rows = texture.getSize().y / spriteHeight;
    int cols = texture.getSize().x / spriteWidth;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) { 
            _frames.emplace_back(sf::IntRect(x * _frameWidth, y * _frameHeight, _frameWidth, _frameHeight));
        }
    }
}
sf::IntRect SpriteSheet::getSpriteRect(size_t index) {
    sf::IntRect spriteRect;
    if (index >= 0 && index < _frames.size()) {
        spriteRect = _frames[index];
    }
    return spriteRect;
}