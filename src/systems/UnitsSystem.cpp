#include "../../include/systems/UnitsSystem.hpp"
//#include "../../include/systems/AnimationSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"
#include <iostream>
UnitsSystem::UnitsSystem(std::vector<Entity>& entities) :SystemBase(entities) {}

void UnitsSystem::update(const sf::Time deltaTime)
{
	for (auto& entity : _entities)
	{
		if (entity.hasComponent<UnitComponent>())
		{
			auto& comp = entity.getComponent<UnitComponent>();
			if (entity.hasComponent<AnimationComponent>()) {
				auto sprite = entity.getComponent<AnimationComponent>().animation.getSprite();
				comp.hpbar.updateBar(comp.hp, comp.maxhp, sprite.getPosition(),sf::Vector2f(32,10));
			}
		}
	}
}