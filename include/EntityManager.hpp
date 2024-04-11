#pragma once

#include "Entity.hpp"

#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/HandleInputComponent.hpp"
#include "components/SelectableComponent.hpp"
#include "components/ResourceComponent.hpp"
#include "components/UnitComponent.hpp"
#include "components/AIComponent.hpp"

#include "systems/TransformSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/UnitsSystem.hpp"
#include "systems/AISystem.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <string>


typedef std::tuple<std::vector<TransformComponent>,
				   std::vector<AnimationComponent>,
				   std::vector<HandleInputComponent>,
				   std::vector<SelectableComponent>,
				   std::vector<CollisionComponent>,
				   std::vector<ResourceComponent>,
				   std::vector<UnitComponent>,
				   std::vector<AIComponent>> EntityComponentVectorTuple;

class EntityMemoryPool;

class EntityManager
{
	private:
		std::vector<Entity> _entities;
		std::vector<Entity> _tiles;
		std::vector<Entity> _units;
		std::vector<Entity> _buildings;

		


	public:
		EntityManager();

		Entity addEntity(const std::string& tag);
		void removeEntity(Entity e);
		void update(const sf::Time deltaTime);
		//void handleEvents(const sf::Event event);
		void render(sf::RenderWindow& window);


		TransformSystem _TransformSystem;
		AnimationSystem _AnimationSystem;
		InputSystem		_InputSystem;
		CollisionSystem _CollisionSystem;
		UnitsSystem		_UnitsSystem;
		AISystem		_AISystem;


		std::vector<Entity>& getEntities();
		std::vector<Entity>& getUnits();
		std::vector<Entity>& getTiles();
		std::vector<Entity>& getBuildings();

	
};

