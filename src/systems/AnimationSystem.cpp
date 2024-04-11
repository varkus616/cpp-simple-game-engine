#include "../../include/systems/AnimationSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"

AnimationSystem::AnimationSystem(std::vector<Entity>& entities) :SystemBase(entities) {}

void AnimationSystem::update(const sf::Time deltaTime)
{

	for (auto& entity : _entities)
		if (entity.hasComponent<AnimationComponent>())
		{
			entity.getComponent<AnimationComponent>().animation.update();
		}
}

void AnimationSystem::render(sf::RenderWindow& window)
{
	for (auto& entity : _entities)
		if (entity.hasComponent<AnimationComponent>())
		{
			AnimationComponent& anC = entity.getComponent<AnimationComponent>();
			window.draw(anC.animation);
			if (entity.hasComponent<UnitComponent>()) {
				
				window.draw(entity.getComponent<UnitComponent>().hpbar.bar);
			}
		}
}