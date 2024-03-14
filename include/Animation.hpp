#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
	private:
		const std::string _name;
		sf::Sprite			_sprite;
		sf::Vector2f		_size;
		size_t				_frameCount;
		size_t				_speed;
		size_t				_currentFrame;
		bool				_repeate;
		

		void update();

		const sf::Vector2f& getSize() const;

		const std::string& getName() const;

		sf::Sprite& getSprite();

		bool hasEnded()const;
	public:
		Animation(const std::string& name, const sf::Texture& texture);
		Animation(const std::string& name, const sf::Texture& texture,
			size_t frameCount, size_t speed);
		Animation();
};