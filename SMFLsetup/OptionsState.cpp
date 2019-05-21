#include "pch.h"

OptionsState::OptionsState(GameDataRef data, std::string songName) : data_(std::move(data)), songName_(std::move(songName)) {}

void OptionsState::init()
{
	infoText_.setString("Is this the song that\nyou wanted to play?");
	infoText_.setFont(data_->assets.getFont("MAIN"));
	infoText_.setCharacterSize(40);
	infoText_.setOutlineThickness(2.f);
	infoText_.setFillColor(sf::Color::White);
	infoText_.setOutlineColor(sf::Color::Black);
	infoText_.setPosition(float(WIN_RES.x / 16), float(WIN_RES.y / 16));

	playText_.setString("play");
	playText_.setFont(data_->assets.getFont("MAIN"));
	playText_.setCharacterSize(35);
	playText_.setOutlineThickness(3.f);
	playText_.setFillColor(sf::Color::Black);
	playText_.setOutlineColor(sf::Color::White);
	playText_.setPosition(float(WIN_RES.x / 2 - playText_.getGlobalBounds().width / 2), float(WIN_RES.y * 0.5));
	
	optionsText_.setString("change key bindings");
	optionsText_.setFont(data_->assets.getFont("MAIN"));
	optionsText_.setCharacterSize(35);
	optionsText_.setOutlineThickness(3.f);
	optionsText_.setFillColor(sf::Color::Black);
	optionsText_.setOutlineColor(sf::Color::White);
	optionsText_.setPosition(float(WIN_RES.x / 2 - optionsText_.getGlobalBounds().width / 2), float(WIN_RES.y * 0.6));

	returnText_.setString("return to menu");
	returnText_.setFont(data_->assets.getFont("MAIN"));
	returnText_.setCharacterSize(35);
	returnText_.setOutlineThickness(3.f);
	returnText_.setFillColor(sf::Color::Black);
	returnText_.setOutlineColor(sf::Color::White);
	returnText_.setPosition(float(WIN_RES.x / 2 - returnText_.getGlobalBounds().width / 2), float(WIN_RES.y * 0.7));

	data_->songsData.getSong(songName_).music.play();
}

void OptionsState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			data_->window.close();
		}
	}
	
	if (InputManager::isTextClicked(playText_,sf::Mouse::Left,data_->window))
	{
		data_->songsData.getSong(songName_).music.stop();
		data_->maschine.addState(std::make_unique<GameState>(data_, songName_), true);
	}
	if (InputManager::isTextClicked(returnText_, sf::Mouse::Left, data_->window))
	{
		data_->songsData.getSong(songName_).music.stop();
		data_->maschine.removeState();
	}
	if (InputManager::isTextClicked(optionsText_, sf::Mouse::Left, data_->window))
	{
		data_->maschine.addState(std::make_unique<KeyBindingState>(data_), false);
	}
}

void OptionsState::update(float dt)
{
}

void OptionsState::draw(float dt)
{
	data_->window.clear(BG_COLOR);
	data_->window.draw(infoText_);
	data_->window.draw(playText_);
	data_->window.draw(returnText_);
	data_->window.draw(optionsText_);
	data_->window.display();
}
