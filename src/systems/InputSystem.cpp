#include "../../include/systems/InputSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"
#include <iostream>
InputSystem::InputSystem(std::vector<Entity>& entities):SystemBase(entities){}

void InputSystem::update(const sf::Time deltaTime)
{
	for (auto& entity : _entities)
	{
		if (entity.hasComponent<SelectableComponent>() && entity.hasComponent<AnimationComponent>())
		{
			sf::Sprite& sprite = entity.getComponent<AnimationComponent>().animation.getSprite();
			if (entity.getComponent<SelectableComponent>().selected)
			{
				sprite.setColor(sf::Color::Red);
			}
			else {
				sprite.setColor(sf::Color::White);
			}
		}
	}
}