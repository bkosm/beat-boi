#pragma once

class EndGameState : public State
{
public:
	EndGameState(GameDataRef data);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;
};
