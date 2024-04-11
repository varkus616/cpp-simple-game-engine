#include "../../include/systems/TransformSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"

TransformSystem::TransformSystem(std::vector<Entity>& entities):SystemBase(entities){}

void TransformSystem::setDestinationForSelectedUnits(const sf::Vector2f& destination) {
	for (auto& entity : _entities) {
		if (entity.hasComponent<SelectableComponent>() && entity.getComponent<SelectableComponent>().selected) {
			if (entity.hasComponent<TransformComponent>()) {
				entity.getComponent<TransformComponent>().destination = destination;
			}
		}
	}
}

void TransformSystem::update(const sf::Time deltaTime) {
    for (auto& entity : _entities) {
        if (entity.hasComponent<TransformComponent>()) {
            TransformComponent& eComp = entity.getComponent<TransformComponent>();
            if (eComp.destination != sf::Vector2f()) {

                sf::Vector2f direction = eComp.destination - eComp.position;
                sf::Vector2f newPosition = eComp.position + (eComp.destination - eComp.position);

                float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                if (distance > 1.0f) {
                    direction /= distance;
                    sf::Vector2f speed = eComp.speed;
                    sf::Vector2f velocity = sf::Vector2f(
                        direction.x * speed.x * deltaTime.asSeconds(),
                        direction.y * speed.y * deltaTime.asSeconds());
                    eComp.position += velocity;
                }
                else {
                    eComp.position = eComp.destination;
                    eComp.destination = sf::Vector2f();
                }
            }

            if (entity.hasComponent<AnimationComponent>()) {
                entity.getComponent<AnimationComponent>().animation.getSprite().setPosition(eComp.position);
            }
        }
    }
}