#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "EntityMemoryPool.hpp"
#include "Command.hpp"



class GameState : public State
{
    public:
        GameState(StateStack& stack, Context context);
        virtual ~GameState();
    
        void render() override;
        bool update(sf::Time deltaTime) override;

    private:
        void executeCommands() override;
        void loadTileMap(const std::string& filename);
        void createTile(int id);
        sf::RenderWindow& _window;
        std::vector<Entity> _tileMap;
        EntityMemoryPool    _EntityMemoryPool;
        EntityManager	    _EntityManager;

    
};