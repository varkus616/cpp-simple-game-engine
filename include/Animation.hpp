#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Animation : public sf::Drawable
{
	private:
		const std::string	_name;
		sf::Sprite			_sprite;
		sf::Vector2f		_size;
		size_t				_frameCount;
		size_t				_speed;
		size_t				_currentFrame;
		bool				_repeate;
	
	public:
		Animation(const std::string& name, const sf::Texture& texture);
		Animation(const std::string& name, const sf::Texture& texture,
			size_t frameCount, size_t speed);
		Animation();
		Animation(const Animation& other);

		void update();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		const sf::Vector2f& getSize() const;

		const sf::Color getBaseColor() const;

		const std::string& getName() const;

		sf::Sprite& getSprite();

		bool hasEnded()const;

};