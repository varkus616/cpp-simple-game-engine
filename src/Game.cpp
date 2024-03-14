#include "../include/Game.hpp"
#include <iostream>


Game::Game():
	_window(sf::VideoMode(1200, 768), "RTS GAME", sf::Style::Default),
	_ResourcesManager(),
	_StateStack(State::Context(_window))
{
	initialize();
}
Game::~Game()
{
}

void Game::initialize()
{
	_window.setVerticalSyncEnabled(true);

	_StateStack.registerState<MenuState>(States::MenuState);
	_StateStack.registerState<GameState>(States::GameState);
	_StateStack.pushState(States::GameState);
}

void Game::run()
{

	sf::Clock clock;
	//sf::Time timeSinceLastUpdate = sf::Time::Zero;
	//float framerate = 1.f / 60.f;

	_ResourcesManager.startUp();
	ResourcesManager::LoadTexture("Assets/Textures/gamer.png", "Gamer");
	ResourcesManager::LoadTexture("Assets/Textures/MapTileSet.png", "MapTileSet");
	while (isRunning())
	{
		
		handleEvents();

		//timeSinceLastUpdate += clock.restart();
		//handleEvents();
		update(clock.restart());

		render();
	}
	_ResourcesManager.shutDown();
}

const bool Game::isRunning()const{return _window.isOpen();}

void Game::handleEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
		}
		
		_StateStack.handleEvent(event);
	}
}

void Game::update(const sf::Time deltaTime)
{
	_StateStack.update(sf::Time::Zero);
}
void Game::render()
{
	_window.clear();

	_StateStack.render();

	_window.display();
}
