#pragma once

class PauseState : public State
{
public:
	PauseState(GameDataRef data);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Text restart_;
};
