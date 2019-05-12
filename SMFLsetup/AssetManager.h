#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager() = default;

	void loadTexture(const std::string& name, const std::string& filename);
	void loadFont(const std::string& name, const std::string& filename);
	void loadSound(const std::string& name, const std::string& filename);

	sf::Texture& getTexture(const std::string& name);
	sf::Font& getFont(const std::string& name);
	sf::SoundBuffer& getSound(const std::string& name);

private:
	std::map<std::string, sf::Texture> textures_;
	std::map<std::string, sf::Font> fonts_;
	std::map<std::string, sf::SoundBuffer> sounds_;
};