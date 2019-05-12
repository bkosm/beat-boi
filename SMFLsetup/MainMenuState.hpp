#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"

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

	sf::Sprite background_;
	sf::Text firstSongText_;
	sf::Sound sound_;
	sf::Music music_;
};