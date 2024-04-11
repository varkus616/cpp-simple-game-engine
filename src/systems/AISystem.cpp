#include "../../include/systems/AISystem.hpp"
#include "../../include/EntityMemoryPool.hpp"

void AISystem::update(const sf::Time deltaTime)
{
    for (auto& entity : _entities) {
        if (entity.hasComponent<AIComponent>()) {
            AIComponent& aiComponent = entity.getComponent<AIComponent>();
            aiComponent.ai.update(deltaTime);
        
        }
    }
}
