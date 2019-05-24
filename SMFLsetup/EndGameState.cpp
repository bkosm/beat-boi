#include "pch.h"

EndGameState::EndGameState(GameDataRef data, std::string songName, const int score, const int combo) : data_(std::move(data)), songName_(std::move(songName)), score_(score), combo_(combo)
{
	bg_.setTexture(data_->assets.getTexture("end bg"));

	scoreText_.setFont(data_->assets.getFont("MAIN"));
	scoreText_.setString(std::to_string(score_));
	scoreText_.setCharacterSize(25);
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, 0);
	scoreText_.setPosition(float(WIN_RES.x * 0.95), float(WIN_RES.y * 0.14));

	comboText_.setFont(data_->assets.getFont("MAIN"));
	comboText_.setString(std::to_string(combo_));
	comboText_.setCharacterSize(25);
	comboText_.setFillColor(sf::Color::White);
	comboText_.setOrigin(comboText_.getGlobalBounds().width, 0);
	comboText_.setPosition(float(WIN_RES.x * 0.95), float(WIN_RES.y * 0.22));

	bestScoreText_.setFont(data_->assets.getFont("MAIN"));
	bestScoreText_.setString(std::to_string(bestScore_));
	bestScoreText_.setCharacterSize(25);
	bestScoreText_.setFillColor(sf::Color::White);
	bestScoreText_.setOrigin(bestScoreText_.getGlobalBounds().width, 0);
	bestScoreText_.setPosition(float(WIN_RES.x * 0.95), float(WIN_RES.y * 0.325));

	exit_.setSize(sf::Vector2f(400, 40));
	exit_.setFillColor(sf::Color::Transparent);
	exit_.setPosition(float(WIN_RES.x * 0.01), float(WIN_RES.y * 0.8));
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
	}

	if (InputManager::isShapeClicked(restart_, sf::Mouse::Left, data_->window))
	{
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<GameState>(data_, songName_), true);
	}
	if (InputManager::isShapeClicked(exit_, sf::Mouse::Left, data_->window))
	{
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
	}
}

void EndGameState::update(float dt)
{
}

void EndGameState::draw(float dt)
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(restart_);
	data_->window.draw(exit_);
	data_->window.draw(scoreText_);
	data_->window.draw(comboText_);
	data_->window.draw(bestScoreText_);
	data_->window.display();
}
