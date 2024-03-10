#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourcesManager
{
	public:
		ResourcesManager();
		~ResourcesManager();
		

		void startUp();
		void shutDown();

		static void LoadTexture(std::string const& filename,
			std::string const& name);

		static sf::Texture& GetTexture(std::string const& name);


	private:
		std::unordered_map<std::string, sf::Texture> _Textures;

		static ResourcesManager* _instance;


};

