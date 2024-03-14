#pragma once
#include <vector>
//#include <SFML/Graphics.hpp>
#include "../Entity.hpp"


namespace sf { class Time; }
class Entity;

class SystemBase
{
	protected:
	std::vector<Entity>& _entities;

	public:
		SystemBase(std::vector<Entity>& entities);
	virtual void update(const sf::Time deltaTime) = 0;
};