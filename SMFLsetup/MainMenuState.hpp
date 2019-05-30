#pragma once

class MainMenuState : public State
{
public:
	MainMenuState(std::shared_ptr<GameData> data);

	void handleInput() override;
	void update() override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Sprite bg_;
	sf::Text enteredText_;
	sf::String stringEntered_;

	bool played_{ false };
};