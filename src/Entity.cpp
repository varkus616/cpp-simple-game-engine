#include "../include/Entity.hpp"
#include "../include/EntityMemoryPool.hpp"
Entity::Entity(size_t id):_id(id){}

const std::string& Entity::getTag()const
{
	return EntityMemoryPool::getTag(_id);
}