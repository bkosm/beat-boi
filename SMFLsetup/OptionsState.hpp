#pragma once

class OptionsState : public State
{
public:
	OptionsState(GameDataRef data, std::string songName);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Sprite bg_;
	sf::RectangleShape play_, viewKeys_, return_;

	std::string songName_;
	bool clicked_{ false };
};
