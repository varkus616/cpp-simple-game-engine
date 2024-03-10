#pragma once
#include "ComponentBase.hpp"
#include <SFML/Graphics.hpp>

struct SpriteComponent : ComponentBase
{
	sf::Sprite sprite;
};
