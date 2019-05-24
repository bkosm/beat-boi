#pragma once

class PauseState : public State
{
public:
	PauseState(GameDataRef data, std::string songName, int score, int maxCombo);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Sprite bg_;
	sf::RectangleShape restart_, exit_;

	std::string songName_;
	int score_, maxCombo_;
};
