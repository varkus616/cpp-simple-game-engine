#pragma once
#include "ComponentBase.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace Role
{
	enum ID : int
	{
		None,
		Player,
		Enemy,
		SIZE
	};

}


struct UnitComponent : ComponentBase
{

	Role::ID role;
	std::string type;
	int hp;
	const int maxhp=100;
	struct HealthBar
	{
		sf::RectangleShape bar;

		HealthBar()
		{
			bar.setFillColor(sf::Color::Red);
			bar.setOutlineColor(sf::Color::Black);
			bar.setOutlineThickness(1.f); 
			bar.setOrigin(bar.getOrigin().x, bar.getOrigin().y + bar.getSize().y);
		}

		void updateBar(int currentHP, int maxHP, sf::Vector2f position, sf::Vector2f size)
		{
			float healthRatio = static_cast<float>(currentHP) / maxHP;
			bar.setSize(sf::Vector2f(size.x * healthRatio, size.y));
			bar.setPosition(position);
		}

	};
	HealthBar hpbar;
	int attackDamage;
	void clear()
	{
		ComponentBase::clear();
		role = Role::ID::None;
		type = "";
		hp = 0;
		attackDamage = 0;
	}

};