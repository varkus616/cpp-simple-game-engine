#include "../../include/systems/TransformSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"

TransformSystem::TransformSystem(std::vector<Entity>& entities):SystemBase(entities){}

void TransformSystem::update(const sf::Time deltaTime)
{

	for (auto& entity:_entities)
		if (entity.hasComponent<TransformComponent>())
		{
			TransformComponent& eComp = entity.getComponent<TransformComponent>();
			eComp.position += eComp.velocity;
		}
}