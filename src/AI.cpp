#include "../include/AI.hpp"

#include "../include/components/TransformComponent.hpp"

#include "../include/EntityMemoryPool.hpp"
PatrolBehavior::PatrolBehavior(const std::vector<sf::Vector2f>& patrolPoints, Entity e) : 
	_patrolPoints(patrolPoints), 
	_currentPatrolIndex(0),
    _entity(e)
{}

void PatrolBehavior::update(sf::Time deltaTime)
{
    if (!_patrolPoints.empty()) {
        sf::Vector2f direction = _patrolPoints[_currentPatrolIndex] - _entity.getComponent<TransformComponent>().position;

        float distanceToPatrolPoint = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distanceToPatrolPoint <= 1.0f) { 
            _currentPatrolIndex = (_currentPatrolIndex + 1) % _patrolPoints.size();
            direction = _patrolPoints[_currentPatrolIndex] - _entity.getComponent<TransformComponent>().position;
        }

        _entity.getComponent<TransformComponent>().destination = direction;
    }
}

void AI::update(sf::Time deltaTime)
{
    if (_behavioreClock.getElapsedTime() >= sf::seconds(1.0f)) {
        if (_activeBehaviore)
            _activeBehaviore->update(deltaTime);
        _behavioreClock.restart();
    }
}
void AI::activate(std::unique_ptr<AIBehavior> behaviore) {
	_activeBehaviore = std::move(behaviore);
}
void AI::deactivate(){
	_activeBehaviore = nullptr;
}
