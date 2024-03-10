#pragma once
#include <vector>
#include "../Entity.hpp"


class Entity;

class SystemBase
{
	protected:
	std::vector<Entity>& _entities;

	public:
		SystemBase(std::vector<Entity>& entities);
	virtual void update(float dt) = 0;
};