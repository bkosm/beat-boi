#pragma once

class KeyBindingState : public State
{
public:
	KeyBindingState(GameDataRef data);

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Text infoText_;
	std::vector<sf::Text> keyTexts_, keyBinds_;
};
