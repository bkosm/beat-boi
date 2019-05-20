#include "pch.h"

EndGameState::EndGameState(GameDataRef data) : data_(std::move(data)) {}

void EndGameState::init()
{
}

void EndGameState::handleInput()
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
			this->data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
		}
	}
}

void EndGameState::update(float dt)
{
}

void EndGameState::draw(float dt)
{
	data_->window.clear(sf::Color::White);
	data_->window.display();
}
