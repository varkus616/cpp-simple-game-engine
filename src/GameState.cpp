#include "../include/GameState.hpp"
#include "../include/ResourcesManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    _window(context.window),
    _EntityMemoryPool(),
    _EntityManager(),
    _sheet(ResourcesManager::GetTexture("MapTileSet"),32,32),
    _view(_window.getView()),
    _PlayerBuilding(0)
    
{
    selectionRect.setFillColor(sf::Color(0, 0, 0, 0)); 
    selectionRect.setOutlineThickness(5.f);
    selectionRect.setOutlineColor(sf::Color::Red);

    registerKeyboardCommand(sf::Keyboard::Space, "SPACE");

    registerMouseCommand(sf::Mouse::Button::Left, "MOUSE_LEFT_CLICK");
    registerMouseCommand(sf::Mouse::Button::Right, "MOUSE_RIGHT_CLICK");
    registerMouseCommand(sf::Event::MouseMoved, "MOUSE_MOVED");

    auto viewsize = _view.getSize();
    _view.setSize(viewsize.x - 40.f, viewsize.y - 40.f );
    auto viewcenter = _view.getCenter();
    auto windowsize = _window.getSize();
    _view.setCenter(windowsize.x /2.f, windowsize.y /2.f);

    numOfBuildingsText.setFont(ResourcesManager::GetFont("Basic"));
    startingText.setFont(ResourcesManager::GetFont("Basic"));
    endingText.setFont(ResourcesManager::GetFont("Basic"));

    endingText.setCharacterSize(24);

    numOfBuildingsText.setCharacterSize(24);
    auto worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(sf::Vector2i(0, _window.getSize().y + 24)));
    numOfBuildingsText.setPosition(worldPos);

    startingText.setCharacterSize(24);
    startingText.setFillColor(sf::Color::Red);
    startingText.setOutlineThickness(2);
    startingText.setOutlineColor(sf::Color::Black);
    startingText.setStyle(sf::Text::Bold);
    startingText.setString("Destroy all enemy buildings ! \n Eat trees to regain your units HP.");
   
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    loadTileMap("Assets\\Maps\\StartingMap");
    auto& entities = _EntityManager.getBuildings();
    for (auto e : entities)
    {
        if (e.hasComponent<UnitComponent>()) {
            if (e.getComponent<UnitComponent>().role == Role::ID::Player) {
                _PlayerBuilding = e;
                break;
            }
        }
    }

    auto pos = _PlayerBuilding.getComponent<TransformComponent>().position;
    worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(static_cast<sf::Vector2i>(pos)));
    createUnits({pos.x+124,pos.y+64}, Role::ID::Player);
    createUnits({pos.x+172,pos.y+64}, Role::ID::Player);
    createUnits({pos.x+224,pos.y+64}, Role::ID::Player);
}

bool findEntity(Entity e, std::vector<Entity>& entities)
{
    for (auto entity : entities)
        if (e == entity)return true;
    return false;
}

GameState::~GameState()
{
}


void GameState::render()
{
    if (enemyBuildings.size() > 0 || findEntity(_PlayerBuilding,_EntityManager.getBuildings())) {
        _EntityManager.render(_window);
        _window.draw(selectionRect);
        _window.draw(numOfBuildingsText);
        _window.draw(startingText);
    }
    else {
        _window.draw(endingText);
    }
}


bool GameState::update(sf::Time deltaTime)
{
    if (enemyBuildings.size() > 0 || findEntity(_PlayerBuilding, _EntityManager.getBuildings())) {

        sf::Time fadeTime = sf::seconds(5.f);
        _textVisibleElapsedTime += deltaTime;
        if (!(_textVisibleElapsedTime <= fadeTime)) {
            startingText.setString("");
        }


        enemyBuildings = findEnemyBuildings();

        auto worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(sf::Vector2i(2, _window.getSize().y - 30)));
        numOfBuildingsText.setString("Enemy Buildings:" + std::to_string(enemyBuildings.size()));
        numOfBuildingsText.setPosition(worldPos);

        worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(sf::Vector2i(_window.getSize().x / 2.f - 150,
            _window.getSize().y / 2.f - 150)));

        startingText.setPosition(worldPos);

        executeCommands();



        auto pos = _PlayerBuilding.getComponent<TransformComponent>().position;
        spawnPlayerUnits(deltaTime, pos);
        spawnEnemies(deltaTime);
        _EntityManager.update(deltaTime);
    }
    else {
        endingText.setString("GAME OVER!\nPress ESC to exit.");
        auto worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(sf::Vector2i(_window.getSize().x / 2.f - 150,
            _window.getSize().y / 2.f - 150)));
        endingText.setPosition(worldPos);

        
    }

    return true;
}

void GameState::executeCommands()
{

    auto mousePos = sf::Mouse::getPosition(_window);
    const float scrollSpeed = 5.0f;

    const sf::Vector2f viewSize = _view.getSize();
    const sf::Vector2u windowSize = _window.getSize();
    //std::cout << _view.getCenter().x - viewSize.x / 2<< " mapsizex:" << MapSize.x << "\n";
    if (mousePos.x >= windowSize.x - 20 && _view.getCenter().x + viewSize.x / 2 < MapSize.x)
    {
        _view.move(scrollSpeed, 0); 
    }
    else if (mousePos.x <= 20 && _view.getCenter().x - viewSize.x / 2 > 0)
    {
        _view.move(-scrollSpeed, 0); 
    }

    if (mousePos.y >= windowSize.y - 20 && _view.getCenter().y + viewSize.y / 2 < MapSize.y)
    {
        _view.move(0, scrollSpeed); 
    }
    else if (mousePos.y <= 20 && _view.getCenter().y - viewSize.y / 2 > 0)
    {
        _view.move(0, -scrollSpeed);
    }
    _window.setView(_view);
    
    mousePos = sf::Mouse::getPosition(_window);
    auto worldPos = static_cast<sf::Vector2i>(_window.mapPixelToCoords(mousePos));

    static sf::Clock clickClock; 
    static const sf::Time doubleClickDelay = sf::milliseconds(250);

    while (!_CommandQueue.empty())
    {
        
        Command& c = _CommandQueue.front();
        if (c.type() == "START")
        {
            if (c.name() == "SPACE")
            {
                _EntityManager._CollisionSystem.toggleBoundingBoxRendering();
            }
            
            if (c.name() == "MOUSE_LEFT_CLICK")
            {

                if (clickClock.getElapsedTime() < doubleClickDelay)
                {
                    //createUnits(static_cast<sf::Vector2f>(worldPos), Role::ID::Player);
                }
                else
                {
                    clickClock.restart();
                    startSelection(worldPos);
                }
            }
            if (c.name() == "MOUSE_RIGHT_CLICK")
            {
                if (clickClock.getElapsedTime() < doubleClickDelay)
                {
                    //createUnits(static_cast<sf::Vector2f>(worldPos), Role::ID::Enemy);
                }
                else
                {
                    clickClock.restart();
                    _EntityManager._TransformSystem.setDestinationForSelectedUnits(static_cast<sf::Vector2f>(worldPos));
                }
            }
        }
        else if (c.type() == "END")
        {
            if (c.name() == "MOUSE_LEFT_CLICK")
            {
                endSelection();
            }
        }
        else if (c.type() == "CONTINUSE")
        {
            if (c.name() == "MOUSE_MOVED")
            {
                continueSelection(worldPos);
            }
        }
        _CommandQueue.pop();
    }
}

typedef std::pair<std::vector<int>, sf::Vector2i> MapData;

MapData loadMapData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<int> data;
    int mapWidth = 0;
    int mapHeight = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        int columns = 0;
        while (std::getline(ss, cell, ',')) {
            cell.erase(std::remove(cell.begin(), cell.end(), ' '), cell.end());
            cell.erase(std::remove(cell.begin(), cell.end(), '\n'), cell.end());
            data.push_back(std::stoi(cell));
            ++columns;
        }
        mapWidth = std::max(mapWidth, columns);
        ++mapHeight;
    }

    sf::Vector2i mapSize = { mapWidth, mapHeight };
    file.close();
    return std::make_pair(data, mapSize);
}

void GameState::loadTileMap(const std::string& filename) {
    std::vector<std::string> mapTypes = { "_Static", "_Dynamic", "_Resources", "_EnemyTownCenter", "_PlayerTownCenter" };
    std::vector<std::vector<int>> data;
    int mapWidth = 0;
    int mapHeight = 0;

    for (const auto& type : mapTypes) {
        try {
            std::string modifiedFilename = filename + type + ".csv";
            MapData mapData = loadMapData(modifiedFilename);
            std::vector<int> map = mapData.first;
            sf::Vector2i size = mapData.second;

            if (size.x > mapWidth) mapWidth = size.x;
            if (size.y > mapHeight) mapHeight = size.y;

            data.push_back(map);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
    MapSize.x = mapWidth*32;
    MapSize.y = mapHeight*32;
    createTiles(data, mapWidth, mapHeight);
}

void GameState::createTiles(const std::vector<std::vector<int>>& ids, int mapWidth, int mapHeight) {
    
    int tileWidth = _sheet.getFrameWidth();
    int tileHeight = _sheet.getFrameHeight();


    
    for (size_t i = 0; i < ids.size(); ++i) {
        const std::vector<int>& tileIds = ids[i];
        for (size_t j = 0; j < tileIds.size(); ++j) {
            int id = tileIds[j];
            if (id == -1) continue;
            int columnIndex = j % mapWidth;
            int rowIndex = j / mapWidth;
            sf::Vector2f pos((float)columnIndex * tileWidth, (float)rowIndex * tileHeight);

            switch (i) {
            case 0: createStaticTile(pos, id);    break;
            case 1: createDynamicTile(pos, id);   break;
            case 2: createResourceTile(pos, id);  break;
            case 3: createEnemyBuilding(pos, id); break;
            case 4: createPlayerBuilding(pos, id);break;
            }
        }
    }

}

void GameState::selectUnits(sf::Vector2f start, sf::Vector2f end)
{
    auto& entities = _EntityManager.getEntities();


    float minX = std::min(start.x, end.x);
    float maxX = std::max(start.x, end.x);
    float minY = std::min(start.y, end.y);
    float maxY = std::max(start.y, end.y);

    for (auto& entity : entities)
    {
        if (entity.hasComponent<TransformComponent>() && entity.hasComponent<SelectableComponent>())
            if (isInsideSquare(entity.getComponent<TransformComponent>().position, minX, maxX, minY, maxY))
            {
                entity.getComponent<SelectableComponent>().selected = true;
            }
    }
}

bool GameState::isInsideSquare(sf::Vector2f point, float minX, float maxX, float minY, float maxY)
{
    return point.x >= minX && point.x <= maxX && point.y >= minY && point.y <= maxY;
}

void GameState::startSelection(const sf::Vector2i& startPosition) {

    auto& entities = _EntityManager.getEntities();

    for (auto& entity : entities)
    {
        if (entity.hasComponent<TransformComponent>() && entity.hasComponent<SelectableComponent>())
            entity.getComponent<SelectableComponent>().selected = false;
    }

    isSelecting = true;
    //auto worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(startPosition));
    selectionStart = static_cast<sf::Vector2f>(startPosition);
    selectionRect.setPosition(sf::Vector2f(selectionStart));
}

void GameState::endSelection() {
    isSelecting = false;
    auto mousePos = sf::Mouse::getPosition(_window);
    auto worldPos = static_cast<sf::Vector2f>(_window.mapPixelToCoords(mousePos));
    selectUnits(selectionRect.getPosition(), worldPos);
    selectionRect.setSize(sf::Vector2f(0,0));
}

void GameState::continueSelection(const sf::Vector2i& currentPosition) {
    if (isSelecting) {
        sf::Vector2f size = sf::Vector2f(static_cast<sf::Vector2f>(currentPosition) - selectionStart);
        selectionRect.setSize(size);
    }
}

void GameState::moveSelectedUnits(const sf::Vector2f& destination) {
    auto& entities = _EntityManager.getEntities();
    for (auto& entity : entities) {
        if (entity.hasComponent<SelectableComponent>() && entity.getComponent<SelectableComponent>().selected) {
            auto unitC = entity.getComponent<UnitComponent>();
            if (unitC.type == "Unit")
                entity.getComponent<TransformComponent>().position = destination;
        }
    }
}

void GameState::createStaticTile(const sf::Vector2f& pos, int id) {
    Entity e = _EntityManager.addEntity("StaticTile");
    e.addComponent<TransformComponent>();
    e.addComponent<AnimationComponent>();
    //e.addComponent<SelectableComponent>();

    e.getComponent<TransformComponent>().position = pos;

    sf::Sprite& sprite = e.getComponent<AnimationComponent>().animation.getSprite();

    sprite.setTexture(ResourcesManager::GetTexture("MapTileSet"));
    sprite.setTextureRect(_sheet.getSpriteRect(id));
    sprite.setPosition(pos);
}

void GameState::createDynamicTile(const sf::Vector2f& pos, int id) {
    Entity e = _EntityManager.addEntity("DynamicTile");
    e.addComponent<TransformComponent>();
    e.addComponent<AnimationComponent>();
    e.addComponent<CollisionComponent>();
     
    e.getComponent<TransformComponent>().position = pos;

    sf::Sprite& sprite = e.getComponent<AnimationComponent>().animation.getSprite();

    sprite.setTexture(ResourcesManager::GetTexture("MapTileSet"));
    sprite.setTextureRect(_sheet.getSpriteRect(id));
    e.getComponent<CollisionComponent>().boundingBox = sprite.getGlobalBounds();

    sprite.setPosition(pos);
}

void GameState::createResourceTile(const sf::Vector2f& pos, int id) {
    Entity e = _EntityManager.addEntity("Resource");
    e.addComponent<TransformComponent>();
    e.addComponent<AnimationComponent>();
    e.addComponent<ResourceComponent>();
    e.addComponent<CollisionComponent>();

    e.getComponent<ResourceComponent>().type = Resources::ID::Wood;
    e.getComponent<ResourceComponent>().amount = 100;

    e.getComponent<TransformComponent>().position = pos;

    sf::Sprite& sprite = e.getComponent<AnimationComponent>().animation.getSprite();

    sprite.setTexture(ResourcesManager::GetTexture("Tree"));
    //sprite.setTextureRect(_sheet.getSpriteRect(id));
    sprite.setPosition(pos);
    e.getComponent<CollisionComponent>().boundingBox = sprite.getGlobalBounds();
}

void GameState::createEnemyBuilding(const sf::Vector2f& pos, int id) {
    Entity e = _EntityManager.addEntity("Building");
    enemyBuildings.push_back(e);
    e.addComponent<TransformComponent>();
    e.addComponent<AnimationComponent>();
    e.addComponent<UnitComponent>();
    e.addComponent<CollisionComponent>();

    e.getComponent<UnitComponent>().role = Role::ID::Enemy;
    e.getComponent<UnitComponent>().type = "Building";
    e.getComponent<UnitComponent>().hp = 200;
    e.getComponent<UnitComponent>().attackDamage = 5;
   

    e.getComponent<TransformComponent>().position = pos;

    sf::Sprite& sprite = e.getComponent<AnimationComponent>().animation.getSprite();

    sprite.setTexture(ResourcesManager::GetTexture("EnemyTownHall"));
    //sprite.setTextureRect(_sheet.getSpriteRect(id));
    sprite.setPosition(pos);
}

void GameState::createPlayerBuilding(const sf::Vector2f& pos, int id) {
    Entity e = _EntityManager.addEntity("Unit");
    e.addComponent<TransformComponent>();
    e.addComponent<AnimationComponent>();
    //e.addComponent<SelectableComponent>();
    e.addComponent<CollisionComponent>();
    e.addComponent<UnitComponent>();

    e.getComponent<UnitComponent>().role = Role::ID::Player;
    e.getComponent<UnitComponent>().type = "Building";
    e.getComponent<UnitComponent>().hp = 200;
    e.getComponent<UnitComponent>().attackDamage = 5;

    e.getComponent<TransformComponent>().position = pos;

    sf::Sprite& sprite = e.getComponent<AnimationComponent>().animation.getSprite();

    sprite.setTexture(ResourcesManager::GetTexture("PlayerTownHall"));
    //sprite.setTextureRect(_sheet.getSpriteRect(id));
    sprite.setPosition(pos);
}

void GameState::createUnits(const sf::Vector2f& pos, Role::ID role)
{
    Entity e = _EntityManager.addEntity("Unit");
    e.addComponent<TransformComponent>();
    e.addComponent<CollisionComponent>();
    e.addComponent<AnimationComponent>();
    e.addComponent<UnitComponent>();

    e.getComponent<UnitComponent>().role = role;
    e.getComponent<UnitComponent>().type = "Unit";
    e.getComponent<UnitComponent>().hp = 100;
    e.getComponent<UnitComponent>().attackDamage = 20;

    e.getComponent<TransformComponent>().position = pos;
    e.getComponent<TransformComponent>().speed = sf::Vector2f(50.f, 50.f);

    sf::Sprite& sprite = e.getComponent<AnimationComponent>().animation.getSprite();
    if (role == Role::ID::Enemy) {
        sprite.setTexture(ResourcesManager::GetTexture("EnemyUnit"));
        e.getComponent<UnitComponent>().attackDamage = 50;
        e.addComponent<AIComponent>();

        auto& aiC = e.getComponent<AIComponent>();

        auto buildingPOs = _PlayerBuilding.getComponent<TransformComponent>().position;

        std::vector<sf::Vector2f> patrolPoints = { {0.f,0.f},{(float)_window.getSize().x,(float)_window.getSize().y}, 
            {(float)_window.getSize().x/2.f,(float)_window.getSize().y/2.f},
            buildingPOs};
        auto aibehavior = std::make_unique<PatrolBehavior>(patrolPoints, e);
        aiC.ai.activate(std::move(aibehavior));
    }
    else {
        sprite.setTexture(ResourcesManager::GetTexture("Unit"));
        e.addComponent<SelectableComponent>();
        float scaleX = sprite.getTexture()->getSize().x / 32;
        float scaleY = sprite.getTexture()->getSize().y / 32;
        //sprite.setScale(scaleX, scaleY);
    }
    e.getComponent<CollisionComponent>().boundingBox = sprite.getGlobalBounds();

    //sprite.setTextureRect(_sheet.getSpriteRect(id));
    sprite.setPosition(pos);
}


std::vector<Entity> GameState::findEnemyBuildings()
{
    std::vector<Entity> enemyBuildings;

    auto& units = _EntityManager.getUnits();
    for (auto& u : units)
    {
        if (u.hasComponent<UnitComponent>())
        {
            auto& UC = u.getComponent<UnitComponent>();
            if (UC.type == "Building" && UC.role == Role::ID::Enemy)
            {
                enemyBuildings.push_back(u);
            }
        }
    }

    return enemyBuildings;
}

void GameState::spawnEnemies(sf::Time dt)
{
    sf::Time spawnTime = sf::seconds(5.5);
    _spawnEnemiesElapsedTime += dt;
    if (_spawnEnemiesElapsedTime >= spawnTime)
    {
        sf::Vector2f positions[4] = { {0,0},{0,MapSize.y},{MapSize.x,0},{MapSize.x,MapSize.y} };
        
        createUnits(positions[rand()%4], Role::ID::Enemy);
        _spawnEnemiesElapsedTime = sf::Time::Zero;
    }
    
}
void GameState::spawnPlayerUnits(sf::Time dt, sf::Vector2f pos)
{

    sf::Time spawnTime = sf::seconds(15.5);
    _spawnPlayerUnitsElapsedTime += dt;
    if (_spawnPlayerUnitsElapsedTime >= spawnTime) {
        pos.x = pos.x > 0 ? pos.x : 1;
        pos.y = pos.y > 0 ? pos.y : 1;
        auto rangeX = (rand() % (int)pos.x + 50) + ((int)pos.x - 50);
        auto rangeY = (rand() % (int)pos.y + 50) + ((int)pos.y - 50);
        auto RandomPos = sf::Vector2f(rangeX, rangeY);

        createUnits(RandomPos, Role::ID::Player);
        _spawnPlayerUnitsElapsedTime = sf::Time::Zero;
    }

}