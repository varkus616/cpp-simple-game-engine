#pragma once
#include <SFML/Graphics.hpp>
class Game
{

	public:	
		void run();
		Game();
		~Game();

	private:
		sf::RenderWindow* _window;
		bool gameOver;
		
		void initialize();
		void handleEvents();
		void render();
		void update(float dt);
		const bool isRunning() const;


};

