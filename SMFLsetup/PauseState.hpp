#pragma once

class PauseState : public State
{
public:
	PauseState(std::shared_ptr<GameData> data, std::string songName, int score, int maxCombo);

	void handleInput() override;
	void update() override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Sprite bg_;
	sf::RectangleShape restart_, exit_;

	std::string songName_;
	int score_, maxCombo_;
};
