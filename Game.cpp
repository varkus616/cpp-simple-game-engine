#include "Game.h"

Game::Game()
{
	initialize();
}
Game::~Game()
{
	delete _window;
}
void Game::run()
{
	while (isRunning())
	{
		handleEvents();
		update(0.f);
		render();
	}

}

const bool Game::isRunning()const
{
	return _window->isOpen();
}

void Game::update(float dt)
{

}
void Game::handleEvents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				_window->close();
			}
		}
	}
}
void Game::render()
{
	_window->clear(sf::Color::Red);
	//Rendering
	_window->display();
}

void Game::initialize()
{
	_window = new sf::RenderWindow(sf::VideoMode(1200, 600),"RTS GAME",sf::Style::Default);
	_window->setVerticalSyncEnabled(true);
}