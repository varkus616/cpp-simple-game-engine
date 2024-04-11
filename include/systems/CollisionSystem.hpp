#pragma once
#include <vector>
#include <SFML/System/Time.hpp>
#include "SystemBase.hpp"
#include "../components/CollisionComponent.hpp"
#include "../components/TransformComponent.hpp"

class CollisionSystem : public SystemBase
{
public:
    CollisionSystem(std::vector<Entity>& entities) : SystemBase(entities) {}
    
    void update(const sf::Time deltaTime) override;
    void renderBoundingBox(sf::RenderWindow& window);
    void toggleBoundingBoxRendering();
    sf::FloatRect getOverlap(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
private:
    sf::Clock attackClock;
    bool _renderingBoundingBox;

};
