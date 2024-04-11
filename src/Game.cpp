#include "../include/Game.hpp"
#include <iostream>


Game::Game():
	_window(sf::VideoMode(960, 614), "RTS GAME", sf::Style::Default),
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

	_ResourcesManager.startUp();

	ResourcesManager::LoadTexture("Assets/Textures/MapTileSet.png", "MapTileSet");
	ResourcesManager::LoadTexture("Assets/Textures/unit.png", "Unit");
	ResourcesManager::LoadTexture("Assets/Textures/enemy_unit.png", "EnemyUnit");
	ResourcesManager::LoadTexture("Assets/Textures/tree.png", "Tree");
	ResourcesManager::LoadTexture("Assets/Textures/player_town_hall.png", "PlayerTownHall");
	ResourcesManager::LoadTexture("Assets/Textures/EnemyTownHall.png", "EnemyTownHall");

	ResourcesManager::LoadFont("Assets/Fonts/NotoSansSymbols-VariableFont_wght.ttf", "Basic");
	//_StateStack.pushState(States::MenuState);
	_StateStack.pushState(States::GameState);

	fpsText.setFont(ResourcesManager::GetFont("Basic"));
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);
}

void Game::run()
{


	while (isRunning())
	{


		deltaTime = clock.restart();

		handleEvents();
		update(deltaTime);
		float fps = 1 / deltaTime.asSeconds();
		std::string fpsString = "FPS: " + std::to_string(static_cast<int>(fps));
		fpsText.setString(fpsString);

		render();
	}
	
	//_ResourcesManager.shutDown();
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
	_StateStack.update(deltaTime);
	auto worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(sf::Vector2i(0,0)));
	fpsText.setPosition(worldPos);
}
void Game::render()
{
	_window.clear();

	_StateStack.render();
	_window.draw(fpsText);
	_window.display();
}
