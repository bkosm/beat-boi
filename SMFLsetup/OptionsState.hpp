#pragma once

class OptionsState : public State
{
public:
	OptionsState(std::shared_ptr<GameData> data, std::string songName);

	void handleInput() override;
	void update() override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Sprite bg_;
	sf::RectangleShape play_, viewKeys_, return_;

	std::string songName_;
	bool clicked_{ false };
};
