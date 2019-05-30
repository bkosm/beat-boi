#include "pch.h"

KeyBindingState::KeyBindingState(std::shared_ptr<GameData> data) : data_(std::move(data))
{
	bg_.setTexture(data_->assets.getTexture("key bg"));
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

void KeyBindingState::update() {}

void KeyBindingState::draw()
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.display();
}
