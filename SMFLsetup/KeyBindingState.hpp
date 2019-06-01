#pragma once

class KeyBindingState : public State
{
public:
	KeyBindingState(std::shared_ptr<GameData> data, std::string songName);

	void handleInput() override;
	void update(float dt) override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Text speedText_;
	sf::Sprite bg_;

	std::string songName_;
};
