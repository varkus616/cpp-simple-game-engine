#pragma once
#include "ComponentBase.hpp"
#include <SFML/Graphics.hpp>

struct TransformComponent : ComponentBase
{
	sf::Vector2f velocity;
	sf::Vector2f position;
};
