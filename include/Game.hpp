#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "EntityManager.hpp"
#include "EntityMemoryPool.hpp"

class Game
{

	public:	
		void run();
		Game();
		~Game();

	private:
		ResourcesManager _ResourcesManager;
		EntityMemoryPool _EntityMemoryPool;
		EntityManager	 _EntityManager;
		sf::RenderWindow* _window;



		bool gameOver;
		
		void initialize();
		void handleEvents();
		void render();
		void update(float dt);
		const bool isRunning() const;


};

