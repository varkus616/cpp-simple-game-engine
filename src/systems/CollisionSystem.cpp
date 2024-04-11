#include "../../include/systems/CollisionSystem.hpp"
#include "../../include/EntityMemoryPool.hpp"
#include <iostream>

void CollisionSystem::update(const sf::Time deltaTime)
{
    for (auto entity : _entities)
    {
        
        if (entity.hasComponent<TransformComponent>() && entity.hasComponent<CollisionComponent>())
        {
            TransformComponent& transform = entity.getComponent<TransformComponent>();
            CollisionComponent& collision = entity.getComponent<CollisionComponent>();
            collision.boundingBox = entity.getComponent<AnimationComponent>().animation.getSprite().getGlobalBounds();

            for (auto otherEntity : _entities)
            {
                if (&entity != &otherEntity && otherEntity.hasComponent<TransformComponent>() && otherEntity.hasComponent<CollisionComponent>())
                {
                    TransformComponent& otherTransform = otherEntity.getComponent<TransformComponent>();
                    CollisionComponent& otherCollision = otherEntity.getComponent<CollisionComponent>();
                    otherCollision.boundingBox = otherEntity.getComponent<AnimationComponent>().animation.getSprite().getGlobalBounds();

                    sf::FloatRect overlap = getOverlap(collision.boundingBox, otherCollision.boundingBox);
                    if (overlap.width > 0 && overlap.height > 0)
                    {
                        if (entity.hasComponent<UnitComponent>() && otherEntity.hasComponent<UnitComponent>())
                        {
                            auto& entityUnitC = entity.getComponent<UnitComponent>();
                            auto& otherEntityUnitC = otherEntity.getComponent<UnitComponent>();
                            
                            if (attackClock.getElapsedTime().asSeconds() >= 0.5)
                            {
                                if ((entityUnitC.role == Role::ID::Player && otherEntityUnitC.role == Role::ID::Enemy) ||
                                    (entityUnitC.role == Role::ID::Enemy  && otherEntityUnitC.role == Role::ID::Player))
                                {
                                    entityUnitC.hp -= otherEntityUnitC.attackDamage;
                                    otherEntityUnitC.hp -= entityUnitC.attackDamage;

                                    attackClock.restart();
                                }
                            }
                            
                        }
                        else if (entity.hasComponent<ResourceComponent>() && otherEntity.hasComponent<UnitComponent>())
                        {
                            auto& RC = entity.getComponent<ResourceComponent>();
                            auto& otherEntityUnitC = otherEntity.getComponent<UnitComponent>();

                            if (attackClock.getElapsedTime().asSeconds() >= 0.5)
                            {
                                if (otherEntityUnitC.role == Role::ID::Player)
                                {
                                    auto& otherEntityUnitC = otherEntity.getComponent<UnitComponent>();
                                    otherEntityUnitC.hp += 7;
                                    RC.amount -= 30;

                                    attackClock.restart();
                                }
                            }
                        }

                        else if (entity.getTag() == "DynamicTile" && otherEntity.hasComponent<UnitComponent>())
                        {
                            otherEntity.getComponent<UnitComponent>().hp = 0;
                        }

                    }
                }
            }
        }
    
    }
    
}

sf::FloatRect CollisionSystem::getOverlap(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
    
    float overlapLeft = std::max(rect1.left, rect2.left);
    float overlapTop = std::max(rect1.top, rect2.top);
    float overlapRight = std::min(rect1.left + rect1.width, rect2.left + rect2.width);
    float overlapBottom = std::min(rect1.top + rect1.height, rect2.top + rect2.height);


    if (overlapRight > overlapLeft && overlapBottom > overlapTop)
    {
        return sf::FloatRect(overlapLeft, overlapTop, overlapRight - overlapLeft, overlapBottom - overlapTop);
    }
    else
    {
        return sf::FloatRect();
    }
}


void CollisionSystem::renderBoundingBox(sf::RenderWindow& window)
{
    if (_renderingBoundingBox) {
        for (auto entity : _entities)
        {
            auto& CollisionC = entity.getComponent<CollisionComponent>();
            CollisionC.box.setFillColor(sf::Color(0,0,0,0));
            CollisionC.box.setOutlineColor(sf::Color(255,255,255,255));
            CollisionC.box.setOutlineThickness(2);
            CollisionC.box.setSize(sf::Vector2f(CollisionC.boundingBox.width, CollisionC.boundingBox.height));
            CollisionC.box.setPosition(entity.getComponent<TransformComponent>().position);
            window.draw(CollisionC.box);
        }
    }
}

void CollisionSystem::toggleBoundingBoxRendering()
{
    if (_renderingBoundingBox)
        _renderingBoundingBox = false;
    else _renderingBoundingBox = true;
}