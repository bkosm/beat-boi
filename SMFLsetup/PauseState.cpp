#include "pch.h"
#include "PauseState.hpp"
#include <utility>

PauseState::PauseState(GameDataRef data) : data_(std::move(data)) {}

void PauseState::init()
{
	resume_.setFont(data_->assets.getFont("AIRFONT"));
	resume_.setPosition(WIN_RES.x - resume_.getGlobalBounds().width / 2, WIN_RES.y / 2);
	resume_.setFillColor(sf::Color::Black);
	resume_.setCharacterSize(60);
}

void PauseState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			data_->window.close();
		}

		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			data_->maschine.removeState();
		}
	}
}

void PauseState::update(float dt)
{
}

void PauseState::draw(float dt)
{
	data_->window.clear(sf::Color(227, 0, 100));
	data_->window.draw(resume_);
	data_->window.display();
}
