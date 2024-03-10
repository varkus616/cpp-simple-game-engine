#include "../include/EntityManager.hpp"
#include "../include/EntityMemoryPool.hpp"
#include <algorithm>


EntityManager::EntityManager():_TransformSystem(_entities){}

void EntityManager::update(float dt)
{
	_TransformSystem.update(dt);
	for (auto& entity : _entities)
	{
		if (entity.hasComponent<TransformComponent>())
		{
			TransformComponent& comp = entity.getComponent<TransformComponent>();
			std::cout << "Entity:" << entity.getId() << " posx:" << comp.xpos << " posy:" << comp.ypos << std::endl;
		}
	}
}
void EntityManager::render(sf::RenderWindow* window)
{
	for (auto& entity : _entities)
	{
		if (entity.hasComponent<SpriteComponent>())
		{
			SpriteComponent& e = entity.getComponent<SpriteComponent>();
			window->draw(e.sprite);
		}
	}
}
void EntityManager::handleEvents(sf::Event event)
{}

Entity EntityManager::addEntity(const std::string& tag)
{
	Entity e = EntityMemoryPool::addEntity(tag);
	_entities.push_back(e);
	return e;
}
void EntityManager::removeEntity(Entity e)
{
	for (auto& en : _entities) { std::cout << "Entity:" << en.getId() << std::endl; }

	_entities.erase(std::remove_if(
		_entities.begin(), _entities.end(), [e](const Entity& entity) {return entity == e; }),
		_entities.end());

	for (auto& en : _entities) { std::cout << "Entity:" << en.getId() << std::endl; }

	EntityMemoryPool::removeEntity(e.getId());
}

std::vector<Entity>& EntityManager::getEntities()
{
	return _entities;
}