#pragma once
#include<vector>
#include<string>
#include<cassert>
#include<iostream>
#include<algorithm>
#include<iostream>
#include "components/TransformComponent.hpp"
#include "EntityManager.hpp"

class EntityMemoryPool
{
	private:
		size_t	_numEntities;
		static EntityMemoryPool* _instance;
		EntityComponentVectorTuple _pool;
		std::vector<std::string> _tags;
		std::vector<bool>		 _active;

		size_t getNextEntityIndex();

	public:
		static size_t  MAX_ENTITIES;
		EntityMemoryPool();

		static Entity addEntity(const std::string& tag)
		{
			size_t index = _instance->getNextEntityIndex();
			
			assert(index != MAX_ENTITIES + 1 && "Error: No more space for entities.");

			_instance->_numEntities++;

			auto& pool = _instance->_pool;

			EntityMemoryPool::getComponent<TransformComponent>(index).active = false;
			EntityMemoryPool::getComponent<SpriteComponent>(index).active = false;

			_instance->_tags[index] = tag;
			_instance->_active[index] = true;

			Entity e(index);
			return e;
		}
		
		static void removeEntity(const size_t id)
		{
			_instance->_numEntities--;
			auto& pool = _instance->_pool;

			EntityMemoryPool::getComponent<TransformComponent>(id).active = false;
			EntityMemoryPool::getComponent<SpriteComponent>(id).active = false;

			_instance->_tags[id] = "";
			_instance->_active[id] = false;
			return;
		}

		template<typename T>
		static T& getComponent(size_t index)
		{
			auto& pool = _instance->_pool;
			return std::get<std::vector<T>>(pool)[index];
		}

		template<typename T>
		static bool hasComponent(size_t index)
		{
			return EntityMemoryPool::getComponent<T>(index).active;
		}

		template<typename T>
		static void addComponent(size_t index)
		{
			EntityMemoryPool::getComponent<T>(index).active = true;
		}

		template <typename T>
		static void removeComponent(size_t index)
		{
			EntityMemoryPool::getComponent<T>(index).active = true;
		}
};
