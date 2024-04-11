#pragma once
#include <SFML/Graphics.hpp>

#include <cstdlib> 
#include <ctime>

#include "State.hpp"
#include "EntityMemoryPool.hpp"
#include "Command.hpp"
#include "SpriteSheet.hpp"
#include "systems/InputSystem.hpp"

class GameState : public State
{
    public:
        GameState(StateStack& stack, Context context);
        virtual ~GameState();
    
        void render() override;
        bool update(sf::Time deltaTime) override;

    private:
        std::vector<Entity> enemyBuildings;

        Entity  _PlayerBuilding;

        sf::Text numOfBuildingsText;
        sf::Text startingText;
        sf::Text endingText;

        sf::Time _textVisibleElapsedTime;
        sf::Time _spawnEnemiesElapsedTime;
        sf::Time _spawnPlayerUnitsElapsedTime;

        sf::Vector2f MapSize;
        bool isSelecting;
        sf::Vector2f selectionStart;
        sf::RectangleShape selectionRect;


        std::vector<Entity> findEnemyBuildings();

        void moveSelectedUnits(const sf::Vector2f& destination);

        void selectUnits(sf::Vector2f start, sf::Vector2f end);

        void spawnEnemies(sf::Time dt);
        void spawnPlayerUnits(sf::Time dt, sf::Vector2f pos);

        bool isInsideSquare(sf::Vector2f point, float minX, float maxX, float minY, float maxY);

        void startSelection(const sf::Vector2i& startPosition);

        void endSelection();

        void continueSelection(const sf::Vector2i& currentPosition);

        //void renderSelectionArea(sf::Vector2i start, sf::Vector2i end);

        void loadTileMap(const std::string& filename);
        void createTiles(const std::vector<std::vector<int>>& ids, int mapWidth, int mapHeight); 
        void createStaticTile(const sf::Vector2f& pos, int id);
        void createDynamicTile(const sf::Vector2f& pos, int id);
        void createResourceTile(const sf::Vector2f& pos, int id);
        void createEnemyBuilding(const sf::Vector2f& pos, int id);
        void createPlayerBuilding(const sf::Vector2f& pos, int id);
        void createPlayerTownCenter(const sf::Vector2f& pos, int id);
        void createUnits(const sf::Vector2f& pos, Role::ID role);
        void executeCommands() override;


        sf::RenderWindow&   _window;

        sf::View _view;

        SpriteSheet         _sheet;

        EntityMemoryPool    _EntityMemoryPool;
        EntityManager	    _EntityManager;

    
};