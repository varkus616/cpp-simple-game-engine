#include "../include/EntityManager.hpp"
#include "../include/EntityMemoryPool.hpp"
#include <algorithm>


EntityManager::EntityManager():_TransformSystem(_entities){}

void EntityManager::update(const sf::Time deltaTime)
{
	_TransformSystem.update(deltaTime);
}
void EntityManager::render(sf::RenderWindow& window)
{
	for (auto& entity : _entities)
	{
		
	}
}

Entity EntityManager::addEntity(const std::string& tag)
{
	Entity e = EntityMemoryPool::addEntity(tag);
	_entities.push_back(e);
	return e;
}
void EntityManager::removeEntity(Entity e)
{

	_entities.erase(std::remove_if(
		_entities.begin(), _entities.end(), [e](const Entity& entity) {return entity == e; }),
		_entities.end());

	EntityMemoryPool::removeEntity(e.getId());
}

std::vector<Entity>& EntityManager::getEntities()
{
	return _entities;
}