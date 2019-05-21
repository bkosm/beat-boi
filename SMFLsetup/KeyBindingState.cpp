#include "pch.h"

KeyBindingState::KeyBindingState(GameDataRef data) : data_(std::move(data))
{
}

void KeyBindingState::init()
{
	infoText_.setString("Press on a button label and then\npress your desired key\nto change the setting.\nThen press ESC to return.");
	infoText_.setFont(data_->assets.getFont("MAIN"));
	infoText_.setCharacterSize(20);
	infoText_.setOutlineThickness(1.f);
	infoText_.setFillColor(sf::Color::White);
	infoText_.setOutlineColor(sf::Color::Black);
	infoText_.setPosition(float(WIN_RES.x * 0.01), float(WIN_RES.y * 0.01));
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
	data_->window.draw(infoText_);
	for (auto& t : keyTexts_) data_->window.draw(t);
	data_->window.display();
}
