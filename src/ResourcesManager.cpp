#include "../include/ResourcesManager.hpp"
#include <assert.h>
#include <iostream>
#include <string>
ResourcesManager* ResourcesManager::_instance = nullptr;

ResourcesManager::ResourcesManager(){}
ResourcesManager::~ResourcesManager() {}

void ResourcesManager::startUp()
{
	assert(_instance == nullptr);
	_instance = this;
}
void ResourcesManager::shutDown()
{
	//delete _instance;
}

sf::Texture& ResourcesManager::GetTexture(std::string const& name)
{
	auto& textureMap = _instance->_Textures;

	auto found = textureMap.find(name);

	if (!(found != textureMap.end())) {
		std::cerr << "Error: Desired texture is not loaded: " << name << std::endl;
		assert(false);
	}

	return found->second;
		
}

void ResourcesManager::LoadTexture(std::string const& filename,
	std::string const& name)
{
	auto& textureMap = _instance->_Textures;

	auto found = textureMap.find(name);

	assert(found == textureMap.end() && "Error: Texture is already loaded");

	sf::Texture texture;
	assert(texture.loadFromFile(filename) && "Error: Can't load a file. Filename error.");
	textureMap.insert(std::make_pair(name,texture));
}

sf::Font& ResourcesManager::GetFont(const std::string& name)
{
	auto& fontMap = _instance->_Fonts;

	auto found = fontMap.find(name);

	if (found == fontMap.end()) {
		std::cerr << "Error: Desired font is not loaded: " << name << std::endl;
		assert(false);
	}

	return found->second;
}

void ResourcesManager::LoadFont(const std::string& filename, const std::string& name)
{
	auto& fontMap = _instance->_Fonts;

	auto found = fontMap.find(name);

	assert(found == fontMap.end() && "Error: Font is already loaded");

	sf::Font font;
	assert(font.loadFromFile(filename) && "Error: Can't load a file. Filename error.");
	fontMap.insert(std::make_pair(name, font));
}