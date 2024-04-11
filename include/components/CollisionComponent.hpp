#pragma once
#include "ComponentBase.hpp"
#include <SFML/Graphics.hpp>

struct CollisionComponent : ComponentBase
{
    sf::FloatRect boundingBox;
    sf::RectangleShape box;
    bool collided;
    void clear()
    {
        ComponentBase::clear();
        boundingBox = sf::FloatRect();
        box = sf::RectangleShape();
    }
};
