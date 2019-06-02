#pragma once
#include "StateMaschine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SongsData.hpp"
#include "Misc.hpp"

struct GameData
{
	sf::RenderWindow window;
	StateMaschine maschine;
	AssetManager assets;
	InputManager input;
	SongsData songsData;
	Settings settings;
	sf::Music backgroundMusic;
	sf::Sound transitionSound, applauseSound;
	float currentMusicVolume{ 100.0f };
};

class Game
{
public:
	Game(unsigned width, unsigned height, const std::string& title);
	~Game() = default;

	static int randInt(int min, int max);

private:
	const float dt_ = FRAMERATE;

	sf::Clock clock_;
	std::shared_ptr<GameData> data_ = std::make_shared<GameData>();

	void run() const;
};