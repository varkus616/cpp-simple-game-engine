#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Entity.hpp"

// Interfejs dla zachowania AI
class AIBehavior {
public:
    virtual ~AIBehavior() {}
    virtual void update(sf::Time deltaTime) = 0;
};

class PatrolBehavior : public AIBehavior {
public:
    PatrolBehavior(const std::vector<sf::Vector2f>& patrolPoints, Entity e);

    void update(sf::Time deltaTime) override;

private:
    std::vector<sf::Vector2f> _patrolPoints;
    std::size_t _currentPatrolIndex;
    Entity _entity;
};


class AI {
public:

    void update(sf::Time deltaTime);

    void activate(std::unique_ptr<AIBehavior> behaviore);

    void deactivate();
private:
    sf::Clock _behavioreClock;
    std::unique_ptr<AIBehavior> _activeBehaviore;
};
