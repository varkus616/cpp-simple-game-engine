#pragma once
//enum class EComponents : unsigned int
//{
//	Transform = 0,
//	SIZE
//};

struct ComponentBase { bool active; virtual void clear() { active = false; } };