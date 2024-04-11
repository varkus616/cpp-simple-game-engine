#pragma once
#include "SystemBase.hpp"
#include "../components/UnitComponent.hpp"

class Command;

class UnitsSystem : SystemBase
{
public:
	UnitsSystem(std::vector<Entity>& entities);
	void update(const sf::Time deltaTime) override;
};
