#include "pch.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>

void AssetManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture tex;

	if (tex.loadFromFile(filename))
	{
		textures_[name] = tex;
	}
}

sf::Texture& AssetManager::getTexture(const std::string& name)
{
	return textures_[name];
}

void AssetManager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font;

	if (font.loadFromFile(filename))
	{
		fonts_[name] = font;
	}
}

void AssetManager::loadSound(const std::string& name, const std::string& filename)
{
	sf::SoundBuffer buffer;

	if (buffer.loadFromFile(filename))
	{
		sounds_[name] = buffer;
	}
}

sf::Font& AssetManager::getFont(const std::string& name)
{
	return fonts_.at(name);
}

sf::SoundBuffer& AssetManager::getSound(const std::string& name)
{
	return sounds_[name];
}
