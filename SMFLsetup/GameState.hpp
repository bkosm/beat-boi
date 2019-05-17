#pragma once
#include "State.h"
#include "Game.h"

struct Hitmarker
{
	sf::Sprite sprite;
	bool isHit{};

	Hitmarker() = default;
	Hitmarker(const sf::Texture& texture, bool hit = false)
	{
		sprite.setTexture(texture);
		isHit = hit;
	}

	bool hasEmptyTex() const
	{
		if (sprite.getTexture()->getSize().x == 1)
		{
			return true;
		}
		return false;
	}
};

struct Settings
{
	sf::Keyboard::Key hit1, hit2, hit3, hit4, strum1, strum2;

	Settings() = default;
};

class GameState : public State
{
public:
	GameState(GameDataRef data, std::string songName);

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;
	DancerSprite dancer_;
	Settings settings_{};

	std::vector<std::vector<Hitmarker>> chart_, onScreen_;
	sf::Sprite firstHitter_, secondHitter_, fourthHitter_, thirdHitter_;
	sf::Text scoreText_, comboText_;
	sf::Sound transitionSound_, hitSound_, strumSound_;
	sf::Clock songClock_, gameClock_;

	std::string songName_;
	int score_{ 0 }, combo_{ 0 }, maxCombo_{ 0 };
	float scrollSpeed_{}, musicDuration_{};
	bool strumOn_{ false };

	void animateHitmarkers_();
	void updateScore_();
	void genDots_();
	void drawDots_();
	void updateDots_();
};
