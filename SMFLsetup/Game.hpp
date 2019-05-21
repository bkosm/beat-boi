#pragma once
#include "StateMaschine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SongsData.hpp"

struct Settings
{
	sf::Keyboard::Key hit1, hit2, hit3, hit4, strum1, strum2, speedUp, speedDown, volumeUp, volumeDown;

	Settings();
	void resetKeyBindings();
};

struct Hitmarker
{
	sf::Sprite sprite;
	bool isHit{};

	Hitmarker() = default;
	Hitmarker(const sf::Texture& texture, bool hit = false);
	bool hasEmptyTex() const;
};

struct GameData
{
	sf::RenderWindow window;
	StateMaschine maschine;
	AssetManager assets;
	InputManager input;
	SongsData songsData;
	Settings settings;
	sf::Music backgroundMusic;
	sf::Sound transitionSound;
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

	DancerSprite();
	void animate(GameDataRef& gameData, const std::string& firstTextureName, const std::string& secondTextureName, float animationDuration);
};