#pragma once
#include "ComponentBase.hpp"
#include "../Animation.hpp"

struct AnimationComponent : ComponentBase
{
	Animation animation;
	AnimationComponent() :animation(){}
	AnimationComponent(const std::string& name, const sf::Texture& texture):animation(name,texture){}
	AnimationComponent(const std::string& name, const sf::Texture& texture,
		size_t frameCount, size_t speed) :animation(name, texture, frameCount, speed){}
};

