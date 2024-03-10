#pragma once
#include "SystemBase.hpp"
#include "../components/TransformComponent.hpp"


class TransformSystem : SystemBase
{
	public:
		TransformSystem(std::vector<Entity>& entities);
	void update(float dt) override;
};
