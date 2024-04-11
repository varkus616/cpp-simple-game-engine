#pragma once
#include "ComponentBase.hpp"
#include <SFML/Graphics.hpp>

struct TransformComponent : ComponentBase
{
	sf::Vector2f speed;
	sf::Vector2f destination;
	sf::Vector2f position;

	void clear()
	{
		ComponentBase::clear();
		destination = position = speed = sf::Vector2f();
	}
};
