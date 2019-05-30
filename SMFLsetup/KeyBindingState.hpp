#pragma once

class KeyBindingState : public State
{
public:
	KeyBindingState(std::shared_ptr<GameData> data);

	void handleInput() override;
	void update() override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Sprite bg_;
};
