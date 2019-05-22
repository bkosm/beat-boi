#include "pch.h"

KeyBindingState::KeyBindingState(GameDataRef data) : data_(std::move(data))
{
}

void KeyBindingState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			data_->window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			data_->transitionSound.play();
			data_->maschine.removeState();
		}
	}
}

void KeyBindingState::update(float dt)
{
}

void KeyBindingState::draw(float dt)
{
	data_->window.clear(BG_COLOR);
	data_->window.draw(bg_);
	data_->window.display();
}
