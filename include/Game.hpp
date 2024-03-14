#pragma once
#include <SFML/Graphics.hpp>

#include "StateStack.hpp"
#include "ResourcesManager.hpp"
#include "EntityManager.hpp"
#include "EntityMemoryPool.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"

class Game
{

	public:	
		void run();
		Game();
		~Game();
	private:
		sf::RenderWindow _window;
		ResourcesManager _ResourcesManager;
		StateStack		 _StateStack;
		
		void initialize();
		void handleEvents();
		void render();
		void update(const sf::Time deltaTime);
		const bool isRunning() const;


};

