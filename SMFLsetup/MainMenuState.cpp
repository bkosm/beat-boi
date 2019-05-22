#include "pch.h"

MainMenuState::MainMenuState(GameDataRef data) : data_(std::move(data))
{
	uiText_.setString("Enter the name of a\nfolder containing\nthe song that\nyou want to play");
	uiText_.setFont(data_->assets.getFont("MAIN"));
	uiText_.setCharacterSize(40);
	uiText_.setOutlineThickness(2.f);
	uiText_.setFillColor(sf::Color::White);
	uiText_.setOutlineColor(sf::Color::Black);
	uiText_.setPosition(float(WIN_RES.x / 16), float(WIN_RES.y / 16));

	textRect_.setSize(sf::Vector2f{ WIN_RES.x * 0.95f, WIN_RES.y * 0.4f });
	textRect_.setOrigin(textRect_.getGlobalBounds().width / 2, textRect_.getGlobalBounds().height / 2);
	textRect_.setPosition(float(WIN_RES.x / 2), float(WIN_RES.y * 0.75f));
	textRect_.setFillColor(sf::Color(255, 255, 255, 100));
	textRect_.setOutlineThickness(2.f);
	textRect_.setOutlineColor(sf::Color::Black);

	enteredText_.setFont(data_->assets.getFont("MAIN"));
	enteredText_.setCharacterSize(45);
	enteredText_.setOutlineThickness(1.f);
	enteredText_.setFillColor(sf::Color::White);
	enteredText_.setOutlineColor(sf::Color::Black);
	enteredText_.setPosition(textRect_.getPosition().x, textRect_.getPosition().y - float(textRect_.getGlobalBounds().height / 8));

	clrText_.setString("press delete to clear");
	clrText_.setCharacterSize(30);
	clrText_.setOutlineThickness(2.f);
	clrText_.setOutlineColor(BG_COLOR);
	clrText_.setFillColor(sf::Color::Black);
	clrText_.setFont(data_->assets.getFont("MAIN"));
	clrText_.setOrigin(clrText_.getGlobalBounds().width / 2, clrText_.getGlobalBounds().height / 2);
	clrText_.setPosition(textRect_.getPosition().x, textRect_.getPosition().y + textRect_.getGlobalBounds().height / 3);
}

void MainMenuState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			data_->window.close();
		}

		if (event.type == sf::Event::TextEntered)
		{
			stringEntered_ += event.text.unicode;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete)
		{
			stringEntered_ = "";
		}
	}
}

void MainMenuState::update(float dt)
{
	if (data_->songsData.loadSong(stringEntered_))
	{
		data_->backgroundMusic.stop();
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<OptionsState>(data_, stringEntered_), true);
	}

	enteredText_.setOrigin(enteredText_.getGlobalBounds().width / 2, enteredText_.getGlobalBounds().height / 2);
	enteredText_.setString(stringEntered_);
}

void MainMenuState::draw(float dt)
{
	data_->window.clear(BG_COLOR);
	data_->window.draw(uiText_);
	data_->window.draw(textRect_);
	data_->window.draw(enteredText_);
	data_->window.draw(clrText_);
	data_->window.display();
}