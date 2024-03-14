#include <SFML/Graphics.hpp>
#include <vector>

class SpriteSheet {
public:
    SpriteSheet(sf::Texture& texture, int spriteWidth, int spriteHeight);

    sf::IntRect getSpriteRect(size_t index);

private:
    sf::Texture&             _texture;
    std::vector<sf::IntRect> _frames;
    int _frameWidth;
    int _frameHeight;
};