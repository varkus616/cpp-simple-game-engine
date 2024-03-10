#include "../include/EntityMemoryPool.hpp"
#include <cassert>

EntityMemoryPool* EntityMemoryPool::_instance = nullptr;
size_t EntityMemoryPool::MAX_ENTITIES = 500;

EntityMemoryPool::EntityMemoryPool()
{
	assert(_instance == nullptr && "Error: Instance of EntityMemoryPool already exists.");
	_instance = this;
	
	std::get<std::vector<TransformComponent>>(_instance->_pool).resize(MAX_ENTITIES);
	std::get<std::vector<SpriteComponent>>(_instance->_pool).resize(MAX_ENTITIES);

	_tags.resize(EntityMemoryPool::MAX_ENTITIES);
	_active.resize(EntityMemoryPool::MAX_ENTITIES);
}

size_t EntityMemoryPool::getNextEntityIndex()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
		if (!_active[i])
			return i;
	return MAX_ENTITIES + 1;
}
