#pragma once

#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"

class EndGameState : public State
{
public:
	EndGameState(GameDataRef data);

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;
};
