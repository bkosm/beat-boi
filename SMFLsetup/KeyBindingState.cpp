#include "pch.h"

KeyBindingState::KeyBindingState(std::shared_ptr<GameData> data) : data_(std::move(data))
{
	bg_.setTexture(data_->assets.getTexture("key bg"));

	speedText_.setFont(data_->assets.getFont("MAIN"));
	speedText_.setCharacterSize(35);
	speedText_.setFillColor(sf::Color::Black);
	speedText_.setPosition(float(WIN_RES.x * 0.65), float(WIN_RES.y * 0.8));
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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			data_->settings.scrollSpeed--;
			if (data_->settings.scrollSpeed < 1)
			{
				data_->settings.scrollSpeed = 1;
			}
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			data_->settings.scrollSpeed++;
			if (data_->settings.scrollSpeed > 15)
			{
				data_->settings.scrollSpeed = 15;
			}
		}
	}
}

void KeyBindingState::update()
{
	speedText_.setString(std::to_string(data_->settings.scrollSpeed));
	speedText_.setOrigin(speedText_.getGlobalBounds().width / 2, 0);
}

void KeyBindingState::draw()
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(speedText_);
	data_->window.display();
}
