#pragma once
#include "ComponentBase.hpp"
#include "../Animation.hpp"

struct AnimationComponent : ComponentBase
{
	Animation animation;
	bool isStatic;
	bool played;
	void clear() { ComponentBase::clear(); animation.getSprite() = sf::Sprite(); }
	
};