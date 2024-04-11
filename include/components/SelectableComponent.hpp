#pragma once
#include "ComponentBase.hpp"

struct SelectableComponent : ComponentBase
{
	bool selected = false;
	void clear() { ComponentBase::clear(); }
};