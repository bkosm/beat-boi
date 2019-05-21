#pragma once

class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Text uiText_, enteredText_, clrText_;
	sf::RectangleShape textRect_;
	sf::String stringEntered_;
};