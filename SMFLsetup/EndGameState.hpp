#pragma once

class EndGameState : public State
{
public:
	EndGameState(GameDataRef data, std::string songName, int score, int combo);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Sprite bg_;
	sf::RectangleShape restart_, exit_;
	sf::Text scoreText_, comboText_, bestScoreText_;

	std::string songName_;
	int score_, combo_, bestScore_{ 0 };
};
