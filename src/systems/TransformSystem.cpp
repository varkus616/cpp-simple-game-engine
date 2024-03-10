#include "../../include/systems/TransformSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"

TransformSystem::TransformSystem(std::vector<Entity>& entities):SystemBase(entities){}

void TransformSystem::update(float dt)
{

	for (auto& entity:_entities)
		if (entity.hasComponent<TransformComponent>())
		{
			TransformComponent& eComp = entity.getComponent<TransformComponent>();
			eComp.xpos += eComp.xvelocity;
			eComp.ypos += eComp.yvelocity;
		}
}