#include "pch.h"
#include "GameState.hpp"
#include "Collision.hpp"
#include "PauseState.hpp"
#include "EndGameState.h"

GameState::GameState(GameDataRef data, std::string songName) : data_(std::move(data)), songName_(std::move(songName)) {}

void GameState::init()
{
	settings_.hit1 = sf::Keyboard::Key::Z;
	settings_.hit2 = sf::Keyboard::Key::X;
	settings_.hit3 = sf::Keyboard::Key::C;
	settings_.hit4 = sf::Keyboard::Key::V;
	settings_.strum1 = sf::Keyboard::Key::Period;
	settings_.strum2 = sf::Keyboard::Key::Slash;

	genDots_();

	firstHitter_.setTexture(data_->assets.getTexture("hit off"));
	secondHitter_.setTexture(data_->assets.getTexture("hit off"));
	thirdHitter_.setTexture(data_->assets.getTexture("hit off"));
	fourthHitter_.setTexture(data_->assets.getTexture("hit off"));
	firstHitter_.setPosition(float(WIN_RES.x / 12), float(WIN_RES.y * 6 / 10));
	secondHitter_.setPosition(float(WIN_RES.x / 4), float(WIN_RES.y * 6 / 10));
	thirdHitter_.setPosition(float(WIN_RES.x * 5 / 12), float(WIN_RES.y * 6 / 10));
	fourthHitter_.setPosition(float(WIN_RES.x * 7 / 12), float(WIN_RES.y * 6 / 10));

	scoreText_.setFont(data_->assets.getFont("MAIN"));
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, scoreText_.getGlobalBounds().height);
	scoreText_.setPosition(float(WIN_RES.x * 0.98), float(WIN_RES.y / 10));
	scoreText_.setFillColor(sf::Color::Black);
	scoreText_.setCharacterSize(45);

	comboText_.setFont(data_->assets.getFont("MAIN"));
	comboText_.setPosition(float(WIN_RES.x * 0.98), float(WIN_RES.y / 5));
	comboText_.setFillColor(sf::Color::Black);
	comboText_.setCharacterSize(35);

	dancer_.sprite.setTexture(data_->assets.getTexture("HANDSUPBOI1"));
	dancer_.sprite.setPosition(float(WIN_RES.x * 8.5 / 10) - dancer_.sprite.getGlobalBounds().width / 2, float(WIN_RES.y / 2));

	transitionSound_.setBuffer(data_->assets.getSound("TRANSITION"));
	hitSound_.setBuffer(data_->assets.getSound("HITSOUND"));
	//hitSound_.setVolume(50.0f);
	transitionSound_.play();
	songClock_.restart();
	gameClock_.restart();
	data_->songsData.getSong(songName_).music.play();

	scrollSpeed_ = 25 * data_->songsData.getSong(songName_).beatDuration;
	musicDuration_ = data_->songsData.getSong(songName_).music.getDuration().asSeconds();
}

void GameState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			data_->window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
		{
			data_->songsData.getSong(songName_).music.pause();
			data_->maschine.addState(std::make_unique<PauseState>(data_), false);
		}

		if (event.type == sf::Event::KeyReleased && (event.key.code == settings_.strum1 || event.key.code == settings_.strum2))
		{
			strumOn_ = true;
		}
	}
}

void GameState::update(float dt)
{
	if (data_->songsData.getSong(songName_).music.getStatus() == sf::SoundSource::Status::Paused)
	{
		data_->songsData.getSong(songName_).music.play();
	}

	if (gameClock_.getElapsedTime().asSeconds() > musicDuration_)
	{
		data_->maschine.addState(std::make_unique<EndGameState>(data_), true);
	}

	animateHitmarkers_();
	updateScore_();
	updateDots_();

	dancer_.animate(data_, "HANDSUPBOI1", "HANDSUPBOI2", data_->songsData.getSong(songName_).beatDuration / 2);
}

void GameState::draw(float dt)
{
	data_->window.clear(sf::Color(227, 0, 64));

	data_->window.draw(scoreText_);
	data_->window.draw(comboText_);
	data_->window.draw(dancer_.sprite);
	data_->window.draw(firstHitter_);
	data_->window.draw(secondHitter_);
	data_->window.draw(fourthHitter_);
	data_->window.draw(thirdHitter_);
	drawDots_();

	data_->window.display();
}

void GameState::animateHitmarkers_()
{
	if (sf::Keyboard::isKeyPressed(settings_.hit1))
	{
		firstHitter_.setTexture(data_->assets.getTexture("hit on"));
	}
	else
	{
		firstHitter_.setTexture(data_->assets.getTexture("hit off"));
	}

	if (sf::Keyboard::isKeyPressed(settings_.hit2))
	{
		secondHitter_.setTexture(data_->assets.getTexture("hit on"));
	}
	else
	{
		secondHitter_.setTexture(data_->assets.getTexture("hit off"));
	}

	if (sf::Keyboard::isKeyPressed(settings_.hit3))
	{
		thirdHitter_.setTexture(data_->assets.getTexture("hit on"));
	}
	else
	{
		thirdHitter_.setTexture(data_->assets.getTexture("hit off"));
	}

	if (sf::Keyboard::isKeyPressed(settings_.hit4))
	{
		fourthHitter_.setTexture(data_->assets.getTexture("hit on"));
	}
	else
	{
		fourthHitter_.setTexture(data_->assets.getTexture("hit off"));
	}
}

void GameState::updateScore_()
{
	if (!chart_.empty())
	{
		for (auto& dots : onScreen_) {
			int currentScore = 0;
			if (Collision::scoreCollision(dots[0].sprite, firstHitter_) && !dots[0].isHit && !dots[0].hasEmptyTex() && sf::Keyboard::isKeyPressed(settings_.hit1) && strumOn_)
			{
				dots[0].isHit = true;
				dots[0].sprite.setTexture(data_->assets.getTexture("EMPTYTEX"));
				currentScore += 5 + combo_;
				combo_++;
				hitSound_.setBuffer(data_->assets.getSound("KICK"));
				hitSound_.play();
			}
			if (Collision::scoreCollision(dots[1].sprite, secondHitter_) && !dots[1].isHit && !dots[1].hasEmptyTex() && sf::Keyboard::isKeyPressed(settings_.hit2) && strumOn_)
			{
				dots[1].isHit = true;
				dots[1].sprite.setTexture(data_->assets.getTexture("EMPTYTEX"));
				currentScore += 5 + combo_;
				combo_++;
				hitSound_.setBuffer(data_->assets.getSound("CLAP"));
				hitSound_.play();
			}
			if (Collision::scoreCollision(dots[2].sprite, thirdHitter_) && !dots[2].isHit && !dots[2].hasEmptyTex() && sf::Keyboard::isKeyPressed(settings_.hit3) && strumOn_)
			{
				dots[2].isHit = true;
				dots[2].sprite.setTexture(data_->assets.getTexture("EMPTYTEX"));
				currentScore += 5 + combo_;
				combo_++;
				hitSound_.setBuffer(data_->assets.getSound("HAT"));
				hitSound_.play();
			}
			if (Collision::scoreCollision(dots[3].sprite, fourthHitter_) && !dots[3].isHit && !dots[3].hasEmptyTex() && sf::Keyboard::isKeyPressed(settings_.hit4) && strumOn_)
			{
				dots[3].isHit = true;
				dots[3].sprite.setTexture(data_->assets.getTexture("EMPTYTEX"));
				currentScore += 5 + combo_;
				combo_++;
				hitSound_.setBuffer(data_->assets.getSound("PERC"));
				hitSound_.play();
			}
			score_ += currentScore;
			strumOn_ = false;
		}
	}

	scoreText_.setString(std::to_string(score_));
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, scoreText_.getGlobalBounds().height);

	comboText_.setString(std::to_string(combo_) + "x");
	comboText_.setOrigin(comboText_.getGlobalBounds().width, comboText_.getGlobalBounds().height);

	if (combo_ > maxCombo_)
	{
		maxCombo_ = combo_;
	}
}

void GameState::genDots_()
{
	for (auto i = 0; i < data_->songsData.getSong(songName_).chart.firstRow.size(); i++)
	{
		std::vector<Hitmarker> temp;

		if (data_->songsData.getSong(songName_).chart.firstRow[i] == true) {
			Hitmarker dot1(data_->assets.getTexture("dot"));
			dot1.sprite.setPosition(float(WIN_RES.x / 12), -dot1.sprite.getGlobalBounds().height);
			temp.emplace_back(dot1);
		}
		else
		{
			Hitmarker dot1(this->data_->assets.getTexture("EMPTYTEX"));
			dot1.sprite.setPosition(float(WIN_RES.x / 12), -dot1.sprite.getGlobalBounds().height);
			temp.emplace_back(dot1);
		}

		if (data_->songsData.getSong(songName_).chart.secondRow[i] == true) {
			Hitmarker dot2(data_->assets.getTexture("dot"));
			dot2.sprite.setPosition(float(WIN_RES.x / 4), -dot2.sprite.getGlobalBounds().height);
			temp.emplace_back(dot2);
		}
		else
		{
			Hitmarker dot2(this->data_->assets.getTexture("EMPTYTEX"));
			dot2.sprite.setPosition(float(WIN_RES.x / 4), -dot2.sprite.getGlobalBounds().height);
			temp.emplace_back(dot2);
		}

		if (data_->songsData.getSong(songName_).chart.thirdRow[i] == true) {
			Hitmarker dot3(data_->assets.getTexture("dot"));
			dot3.sprite.setPosition(float(WIN_RES.x * 5 / 12), -dot3.sprite.getGlobalBounds().height);
			temp.emplace_back(dot3);
		}
		else
		{
			Hitmarker dot3(this->data_->assets.getTexture("EMPTYTEX"));
			dot3.sprite.setPosition(float(WIN_RES.x * 5 / 12), -dot3.sprite.getGlobalBounds().height);
			temp.emplace_back(dot3);
		}

		if (data_->songsData.getSong(songName_).chart.fourthRow[0] == true) {
			Hitmarker dot4(data_->assets.getTexture("dot"));
			dot4.sprite.setPosition(float(WIN_RES.x * 7 / 12), -dot4.sprite.getGlobalBounds().height);
			temp.emplace_back(dot4);
		}
		else
		{
			Hitmarker dot4(this->data_->assets.getTexture("EMPTYTEX"));
			dot4.sprite.setPosition(float(WIN_RES.x * 7 / 12), -dot4.sprite.getGlobalBounds().height);
			temp.emplace_back(dot4);
		}

		chart_.emplace_back(temp);
	}
}


void GameState::drawDots_()
{
	for (const auto& i : onScreen_)
	{
		for (const auto& j : i)
		{
			data_->window.draw(j.sprite);
		}
	}
}

void GameState::updateDots_()
{
	if (songClock_.getElapsedTime().asSeconds() > data_->songsData.getSong(songName_).beatDuration && !chart_.empty())
	{
		onScreen_.push_back(chart_[0]);
		chart_.erase(chart_.begin());
		songClock_.restart();
	}

	for (auto& i : onScreen_)
	{
		for (auto& j : i)
		{
			j.sprite.move(0, scrollSpeed_);
			if (j.sprite.getPosition().y > WIN_RES.y)
			{
				for (auto& dot : *onScreen_.begin())
				{
					if (!dot.hasEmptyTex())
					{
						this->combo_ = 0;
					}
				}

				onScreen_.erase(onScreen_.begin());
				break;
			}
		}
	}
}