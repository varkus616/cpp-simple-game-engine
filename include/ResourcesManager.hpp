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

		static sf::Font& GetFont(const std::string& name);
		static void LoadFont(const std::string& filename, const std::string& name);


	private:
		std::unordered_map<std::string, sf::Texture> _Textures;
		std::unordered_map<std::string, sf::Font>	 _Fonts;

		static ResourcesManager* _instance;


};

