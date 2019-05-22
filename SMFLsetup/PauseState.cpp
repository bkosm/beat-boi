#include "pch.h"

PauseState::PauseState(GameDataRef data) : data_(std::move(data))
{
	restart_.setFont(data_->assets.getFont("MAIN"));
	restart_.setPosition(float(WIN_RES.x - restart_.getGlobalBounds().width / 2), float(WIN_RES.y / 2));
	restart_.setFillColor(sf::Color::Black);
	restart_.setCharacterSize(60);
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
			data_->maschine.addState(std::make_unique<EndGameState>(data_), true);
		}
	}
}

void PauseState::update(float dt)
{
}

void PauseState::draw(float dt)
{
	data_->window.clear(sf::Color(227, 0, 100));
	data_->window.draw(restart_);
	data_->window.display();
}
