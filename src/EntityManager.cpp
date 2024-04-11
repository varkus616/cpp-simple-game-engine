#include "../include/EntityManager.hpp"
#include "../include/EntityMemoryPool.hpp"
#include <algorithm>


EntityManager::EntityManager() :
	_TransformSystem(_entities),
	_AnimationSystem(_entities),
	_InputSystem(_entities),
	_CollisionSystem(_units),
	_UnitsSystem(_units),
	_AISystem(_units)

{
	
}

void EntityManager::update(const sf::Time deltaTime)
{
	for (auto entity : _entities)
	{
		if (entity.hasComponent<UnitComponent>())
		{
			auto& UC = entity.getComponent<UnitComponent>();
			if (UC.hp <= 0)
				removeEntity(entity);

		}
		if (entity.hasComponent<ResourceComponent>()) {
			auto& RC = entity.getComponent<ResourceComponent>();
			
			if (RC.amount <= 0)
				removeEntity(entity);
		}
	}

	_InputSystem.update(deltaTime);
	_TransformSystem.update(deltaTime);
	_CollisionSystem.update(deltaTime);
	_UnitsSystem.update(deltaTime);
	_AnimationSystem.update(deltaTime);
	_AISystem.update(deltaTime);
	
}
void EntityManager::render(sf::RenderWindow& window)
{
	_AnimationSystem.render(window);
	_CollisionSystem.renderBoundingBox(window);
}

Entity EntityManager::addEntity(const std::string& tag)
{
	Entity e = EntityMemoryPool::addEntity(tag);
	_entities.push_back(e);

	if (tag == "Tile")
		_tiles.push_back(e);
	else if (tag == "Unit" || tag == "Resource" || tag == "Building")
		_units.push_back(e);

	return e;
}
void EntityManager::removeEntity(Entity e)
{

	_entities.erase(std::remove_if(
		_entities.begin(), _entities.end(), [e](const Entity& entity) {return entity == e; }),
		_entities.end());
	
	if (e.getTag() == "Tile")
		_tiles.erase(std::remove_if(
			_tiles.begin(), _tiles.end(), [e](const Entity& entity) {return entity == e; }),
			_tiles.end());
	else if (e.getTag() == "Unit" || e.getTag() == "Resource" || e.getTag() == "Building")
		_units.erase(std::remove_if(
			_units.begin(), _units.end(), [e](const Entity& entity) {return entity == e; }),
			_units.end());
	EntityMemoryPool::removeEntity(e.getId());
}

std::vector<Entity>& EntityManager::getEntities()
{
	return _entities;
}
std::vector<Entity>& EntityManager::getUnits()
{
	return _units;
}
std::vector<Entity>& EntityManager::getTiles()
{
	return _tiles;
}
std::vector<Entity>& EntityManager::getBuildings()
{
	return _buildings;
}