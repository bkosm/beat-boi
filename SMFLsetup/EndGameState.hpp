#pragma once

class EndGameState : public State
{
public:
	EndGameState(std::shared_ptr<GameData> data, std::string songName, int score, int combo);

	void handleInput() override;
	void update(float dt) override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Sprite bg_;
	sf::RectangleShape restart_, exit_;
	sf::Text scoreText_, comboText_, bestScoreText_, bestComboText_;

	std::string songName_, bestScore_, bestCombo_;
	int score_, combo_;
	bool clicked_{ false }, processed_{ false };

	void processBestScore_();
};
