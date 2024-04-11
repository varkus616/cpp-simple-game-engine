#pragma once
#include "SystemBase.hpp"
#include "../components/AIComponent.hpp" 

class AISystem : public SystemBase {
public:
    AISystem(std::vector<Entity>& entities) : SystemBase(entities) {}

    void update(const sf::Time deltaTime) override;

};

