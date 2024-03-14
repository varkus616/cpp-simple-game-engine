#include "../include/GameState.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    _window(context.window),
    _EntityMemoryPool(),
    _EntityManager()
    
{
    loadTileMap("Assets\\Maps\\MapaTest.csv");
    registerCommand(sf::Keyboard::Space, "UP");
}

GameState::~GameState()
{
}


void GameState::render()
{
    _EntityManager.render(_window);
}

bool GameState::update(sf::Time deltaTime)
{
    executeCommands();
    _EntityManager.update(deltaTime);
    return true;
}

void GameState::executeCommands()
{
    while (!_CommandQueue.empty())
    {
        Command& c = _CommandQueue.front();
        if (c.type() == "START")
            std::cout << "Hello :D" << std::endl;
        _CommandQueue.pop();
    }
}

void GameState::loadTileMap(const std::string& filename)
{
    std::vector<int> data;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return ; 
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {

            cell.erase(remove(cell.begin(), cell.end(), ' '), cell.end());
            cell.erase(remove(cell.begin(), cell.end(), '\n'), cell.end());
            data.push_back(std::stoi(cell));
        }
    }

    file.close();
    
}

void GameState::createTile(int id)
{
    switch (id)
    {
    case 1:
        break;
    case 2:
        break;

    default:
        break;
    }
}