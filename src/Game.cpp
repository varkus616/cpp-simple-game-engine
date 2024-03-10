#include "../include/Game.hpp"
#include <iostream>


Game::Game():
	_ResourcesManager(),
	_EntityMemoryPool(),
	_EntityManager()
{
	initialize();
}
Game::~Game()
{
	delete _window;
}

void Game::initialize()
{
	_window = new sf::RenderWindow(sf::VideoMode(300, 300), "RTS GAME", sf::Style::Default);
	_window->setVerticalSyncEnabled(true);
}

void Game::run()
{

	sf::Clock clock;
	//sf::Time timeSinceLastUpdate = sf::Time::Zero;
	float framerate = 1.f / 60.f;

	_ResourcesManager.startUp();
	ResourcesManager::LoadTexture("Assets/Textures/gamer.png", "Gamer");
	while (isRunning())
	{
		handleEvents();

		//timeSinceLastUpdate += clock.restart();
		//handleEvents();
		update(clock.restart().asSeconds());

		render();
	}
	_ResourcesManager.shutDown();
}

const bool Game::isRunning()const{return _window->isOpen();}

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
			if (event.key.code == sf::Keyboard::Space)
			{
				Entity e = _EntityManager.addEntity("Dupa");
				e.addComponent<TransformComponent>();
				std::cout << e.hasComponent<TransformComponent>() << std::endl;
				e.getComponent<TransformComponent>().xvelocity = 0.021f;
				e.getComponent<TransformComponent>().yvelocity = 0.00003f;
				e.addComponent<SpriteComponent>();
				e.getComponent<SpriteComponent>().sprite.setTexture(ResourcesManager::GetTexture("Gamer"));
				e.getComponent<SpriteComponent>().sprite.setScale(0.1,0.1);
				e.getComponent<SpriteComponent>().sprite.setColor(sf::Color(5, 255, 0, 255));
				e.getComponent<SpriteComponent>().sprite.setPosition(e.getComponent<TransformComponent>().xpos,
					e.getComponent<TransformComponent>().ypos);
				
			}
		}
		_EntityManager.handleEvents(event);
	}
}

void Game::update(float dt)
{
	_EntityManager.update(dt);
}
void Game::render()
{
	_window->clear(sf::Color::Red);
	_EntityManager.render(_window);
	_window->display();
}
