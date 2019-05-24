#pragma once

class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Sprite bg_;
	sf::Text enteredText_;
	sf::String stringEntered_;

	bool played_{ false };
};