#pragma once
#include<string>
class EntityMemoryPool;

class Entity
{
	private:
		size_t _id;

	public:
		Entity(size_t id);
		
		bool operator==(const Entity& other) const
		{
			return _id == other._id;
		}

		const size_t getId() const{ return _id; }

		const std::string& getTag() const;

		template<typename T>
		T& getComponent()const{return EntityMemoryPool::getComponent<T>(_id);}
		
		template<typename T>
		void addComponent(){EntityMemoryPool::addComponent<T>(_id);}

		template<typename T>
		void removeComponent(){EntityMemoryPool::removeComponent<T>(_id);}

		template<typename T>
		const bool hasComponent() const {return EntityMemoryPool::hasComponent<T>(_id);}

};

