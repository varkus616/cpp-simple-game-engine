#pragma once
#include "SystemBase.hpp"
#include "../components/HandleInputComponent.hpp"
#include "../components/SelectableComponent.hpp"

class Command;

class InputSystem : SystemBase
{
public:
	InputSystem(std::vector<Entity>& entities);
	void update(const sf::Time deltaTime) override;
};
