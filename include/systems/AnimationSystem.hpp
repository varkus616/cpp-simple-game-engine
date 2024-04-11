#pragma once
#include "SystemBase.hpp"
#include "../components/AnimationComponent.hpp"


class AnimationSystem : SystemBase
{
public:
	AnimationSystem(std::vector<Entity>& entities);
	void update(const sf::Time deltaTime) override;
	void render(sf::RenderWindow& window);
};
