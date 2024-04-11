	#pragma once
#include "ComponentBase.hpp"

struct HandleInputComponent : ComponentBase
{
	bool inputHandle = false;
	void clear() { ComponentBase::clear(); }
};