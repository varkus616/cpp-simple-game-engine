#pragma once
#include "ComponentBase.hpp"
#include <string>

namespace Resources
{
	enum ID : int
	{
		None = 1,
		Wood,
		SIZE
	};
}

struct ResourceComponent : ComponentBase
{
	Resources::ID type;
	float amount;
	void clear()
	{
		ComponentBase::clear();
		type = Resources::ID::None;
		amount = 0;
	}
};