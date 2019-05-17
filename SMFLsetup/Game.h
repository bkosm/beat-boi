#pragma once
#include "GlobalConstants.hpp"
#include "StateMaschine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "SongsData.hpp"
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

struct GameData
{
	sf::RenderWindow window;
	StateMaschine maschine;
	AssetManager assets;
	InputManager input;
	SongsData songsData;
	sf::Music backgroundMusic;
};


typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(unsigned width, unsigned height, const std::string& title);
	~Game() = default;

	static int randInt(int min, int max);

private:
	const float dt_ = FRAMERATE;

	sf::Clock clock_;
	GameDataRef data_ = std::make_shared<GameData>();

	void run() const;
};

struct DancerSprite
{
	sf::Sprite sprite;
	sf::Clock clock;
	sf::IntRect frame{ 0, 0, BOI_ANIMATION_HORIZONTAL, BOI_ANIMATION_VERTICAL };
	bool isFirst = true;

	DancerSprite()
	{
		sprite.setTextureRect(frame);
	}

	void animate(GameDataRef& gameData, const std::string& firstTextureName, const std::string& secondTextureName, float animationDuration);
};