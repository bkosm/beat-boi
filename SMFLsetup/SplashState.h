#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"

class SplashState : public State
{
public:
	SplashState(GameDataRef data);

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;
	DancerSprite dancer_;

	sf::Clock clock_;
	sf::Sprite background_;
	sf::Music music_;
};
