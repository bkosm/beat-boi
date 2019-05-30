#include "pch.h"

PauseState::PauseState(std::shared_ptr<GameData> data, std::string songName, const int score, const int maxCombo) :
	data_(std::move(data)),
	songName_(std::move(songName)),
	score_(score),
	maxCombo_(maxCombo)
{
	bg_.setTexture(data_->assets.getTexture("paused bg"));

	restart_.setSize(sf::Vector2f(500, 45));
	restart_.setFillColor(sf::Color::Transparent);
	restart_.setPosition(float(WIN_RES.x / 2 - restart_.getGlobalBounds().width / 2), float(WIN_RES.y / 2 - restart_.getGlobalBounds().height));

	exit_.setSize(sf::Vector2f(500, 45));
	exit_.setFillColor(sf::Color::Transparent);
	exit_.setPosition(float(WIN_RES.x / 2 - exit_.getGlobalBounds().width / 2), float(WIN_RES.y / 2 + exit_.getGlobalBounds().height));
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
	}

	if (InputManager::isShapeClicked(restart_, sf::Mouse::Left, data_->window))
	{
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<GameState>(data_, songName_), true);
	}
	if (InputManager::isShapeClicked(exit_, sf::Mouse::Left, data_->window))
	{
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<EndGameState>(data_, songName_, score_, maxCombo_), true);
	}
}

void PauseState::update() {}

void PauseState::draw()
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(restart_);
	data_->window.draw(exit_);
	data_->window.display();
}
