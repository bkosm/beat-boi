#pragma once

class KeyBindingState : public State
{
public:
	KeyBindingState(std::shared_ptr<GameData> data);

	void handleInput() override;
	void update(float dt) override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Text speedText_;
	sf::Sprite bg_;
};
