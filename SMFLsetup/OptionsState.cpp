#include "pch.h"

OptionsState::OptionsState(GameDataRef data, std::string songName) : data_(std::move(data)), songName_(std::move(songName))
{
	bg_.setTexture(data_->assets.getTexture("options bg"));

	play_.setSize(sf::Vector2f(400, 25));
	play_.setFillColor(sf::Color::Transparent);
	play_.setPosition(float(WIN_RES.x / 2 - play_.getGlobalBounds().width / 2), float(WIN_RES.y / 2 - 2 * play_.getGlobalBounds().height));

	viewKeys_.setSize(sf::Vector2f(400, 25));
	viewKeys_.setFillColor(sf::Color::Transparent);
	viewKeys_.setPosition(float(WIN_RES.x / 2 - viewKeys_.getGlobalBounds().width / 2), float(WIN_RES.y / 2));

	return_.setSize(sf::Vector2f(400, 25));
	return_.setFillColor(sf::Color::Transparent);
	return_.setPosition(float(WIN_RES.x / 2 - return_.getGlobalBounds().width / 2), float(WIN_RES.y / 2 + 2 * return_.getGlobalBounds().height));

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

	if (InputManager::isShapeClicked(play_, sf::Mouse::Left, data_->window) && !clicked_)
	{
		clicked_ = true;
		data_->songsData.getSong(songName_).music.stop();
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<GameState>(data_, songName_), true);
	}
	if (InputManager::isShapeClicked(viewKeys_, sf::Mouse::Left, data_->window))
	{
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<KeyBindingState>(data_), false);
	}
	if (InputManager::isShapeClicked(return_, sf::Mouse::Left, data_->window))
	{
		data_->songsData.getSong(songName_).music.stop();
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
	}
}

void OptionsState::update(float dt)
{
}

void OptionsState::draw(float dt)
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(play_);
	data_->window.draw(viewKeys_);
	data_->window.draw(return_);
	data_->window.display();
}
