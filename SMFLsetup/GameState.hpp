#pragma once

class GameState : public State
{
public:
	GameState(std::shared_ptr<GameData> data, std::string songName);

	void handleInput() override;
	void update(float dt) override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	std::vector<std::vector<Hitmarker>> chart_{}, onScreen_{};
	EffectParticles particles_;
	sf::Sprite firstHitter_, secondHitter_, fourthHitter_, thirdHitter_, bg_;
	sf::Text scoreText_, comboText_;
	sf::Sound hitSound_;
	sf::Clock songClock_, gameClock_;

	std::string songName_;
	int score_{ 0 }, combo_{ 0 }, maxCombo_{ 0 };
	float musicDuration_{}, currentVolume_{ 100.f }, timeAccumulator_{ 0.0f };

	void animateHitmarkers_();
	void updateScore_();
	void genDots_();
	void drawDots_();
	void updateDots_(float dt);
};
