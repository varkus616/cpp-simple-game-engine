#pragma once

#include "Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "systems/TransformSystem.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <string>


typedef std::tuple<std::vector<TransformComponent>,
				   std::vector<AnimationComponent>> EntityComponentVectorTuple;

class EntityMemoryPool;

class EntityManager
{
	private:
		std::vector<Entity> _entities;
		
		TransformSystem _TransformSystem;

	public:
		EntityManager();

		Entity addEntity(const std::string& tag);
		void removeEntity(Entity e);
		void update(const sf::Time deltaTime);
		//void handleEvents(const sf::Event event);
		void render(sf::RenderWindow& window);

		std::vector<Entity>& getEntities();

	
};

