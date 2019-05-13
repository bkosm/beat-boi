#include "pch.h"
#include "GameState.hpp"
#include "Collision.hpp"

GameState::GameState(GameDataRef data, std::string songName) : data_(std::move(data)), songName_(std::move(songName)) {}

void GameState::init()
{
	settings_.hit1 = sf::Keyboard::Key::Z;
	settings_.hit2 = sf::Keyboard::Key::X;
	settings_.hit3 = sf::Keyboard::Key::C;
	settings_.hit4 = sf::Keyboard::Key::V;
	settings_.strum1 = sf::Keyboard::Key::Period;
	settings_.strum2 = sf::Keyboard::Key::Slash;

	this->genDots();

	this->firstHitter_.setTexture(this->data_->assets.getTexture("1 hit off"));
	this->firstHitter_.setPosition(float(WIN_RES.x / 12), float(WIN_RES.y * 8 / 10));
	this->secondHitter_.setTexture(this->data_->assets.getTexture("2 hit off"));
	this->secondHitter_.setPosition(float(WIN_RES.x / 4), float(WIN_RES.y * 8 / 10));
	this->thirdHitter_.setTexture(this->data_->assets.getTexture("3 hit off"));
	this->thirdHitter_.setPosition(float(WIN_RES.x * 5 / 12), float(WIN_RES.y * 8 / 10));
	this->fourthHitter_.setTexture(this->data_->assets.getTexture("4 hit off"));
	this->fourthHitter_.setPosition(float(WIN_RES.x * 7 / 12), float(WIN_RES.y * 8 / 10));

	this->scoreText_.setFont(this->data_->assets.getFont("AIRFONT"));
	this->scoreText_.setOrigin(this->scoreText_.getGlobalBounds().width, this->scoreText_.getGlobalBounds().height);
	this->scoreText_.setPosition(float(WIN_RES.x * 9.5 / 10), float(WIN_RES.y / 10));
	this->scoreText_.setFillColor(sf::Color::Black);
	this->scoreText_.setCharacterSize(60);

	this->comboText_.setFont(this->data_->assets.getFont("AIRFONT"));
	this->comboText_.setPosition(float(WIN_RES.x * 9.5 / 10), float(WIN_RES.y / 5));
	this->comboText_.setFillColor(sf::Color::Black);
	this->comboText_.setCharacterSize(50);

	this->dancer_.sprite.setTexture(this->data_->assets.getTexture("HANDSUPBOI1"));
	this->dancer_.sprite.setPosition(float(WIN_RES.x * 8.5 / 10) - this->dancer_.sprite.getGlobalBounds().width / 2, float(WIN_RES.y / 2));

	this->transitionSound_.setBuffer(this->data_->assets.getSound("TRANSITION"));
	this->hitSound_.setBuffer(this->data_->assets.getSound("HITSOUND"));
	this->hitSound_.setVolume(50.0f);
	this->transitionSound_.play();
	this->songClock_.restart();
	this->data_->songsData.getSong(this->songName_).music.play();

	this->scrollSpeed_ = 20 * this->data_->songsData.getSong(this->songName_).beatDuration;
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
	}
}

void GameState::update(float dt)
{
	this->animateHitmarkers();
	this->updateScore();
	this->updateDots();
	this->dancer_.animate(this->data_, "HANDSUPBOI1", "HANDSUPBOI2", this->data_->songsData.getSong(this->songName_).beatDuration / 2);
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
	drawDots();

	data_->window.display();
}

void GameState::animateHitmarkers()
{
	if (sf::Keyboard::isKeyPressed(settings_.hit1))
	{
		this->firstHitter_.setTexture(this->data_->assets.getTexture("1 hit on"));
	}
	else
	{
		this->firstHitter_.setTexture(this->data_->assets.getTexture("1 hit off"));
	}

	if (sf::Keyboard::isKeyPressed(settings_.hit2))
	{
		this->secondHitter_.setTexture(this->data_->assets.getTexture("2 hit on"));
	}
	else
	{
		this->secondHitter_.setTexture(this->data_->assets.getTexture("2 hit off"));
	}

	if (sf::Keyboard::isKeyPressed(settings_.hit3))
	{
		this->thirdHitter_.setTexture(this->data_->assets.getTexture("3 hit on"));
	}
	else
	{
		this->thirdHitter_.setTexture(this->data_->assets.getTexture("3 hit off"));
	}

	if (sf::Keyboard::isKeyPressed(settings_.hit4))
	{
		this->fourthHitter_.setTexture(this->data_->assets.getTexture("4 hit on"));
	}
	else
	{
		this->fourthHitter_.setTexture(this->data_->assets.getTexture("4 hit off"));
	}
}

void GameState::updateScore()
{
	if (!this->chart_.empty())
	{
		for (auto& dots : this->onScreen_) {
			if (Collision::scoreCollision(dots[0].sprite, this->firstHitter_) && !dots[0].isHit && sf::Keyboard::isKeyPressed(settings_.hit1) && (sf::Keyboard::isKeyPressed(settings_.strum1) || sf::Keyboard::isKeyPressed(settings_.strum2)))
			{
				dots[0].isHit = true;
				dots[0].sprite.setTexture(this->data_->assets.getTexture("EMPTYTEX"));
				this->score_ += 1 * this->combo_;
				this->combo_++;
				this->hitSound_.play();
			}
			if (Collision::scoreCollision(dots[1].sprite, this->secondHitter_) && !dots[1].isHit && sf::Keyboard::isKeyPressed(settings_.hit2) && (sf::Keyboard::isKeyPressed(settings_.strum1) || sf::Keyboard::isKeyPressed(settings_.strum2)))
			{
				dots[1].isHit = true;
				dots[1].sprite.setTexture(this->data_->assets.getTexture("EMPTYTEX"));
				this->score_ += 1 * this->combo_;
				this->combo_++;
				this->hitSound_.play();
			}
			if (Collision::scoreCollision(dots[2].sprite, this->thirdHitter_) && !dots[2].isHit && sf::Keyboard::isKeyPressed(settings_.hit3) && (sf::Keyboard::isKeyPressed(settings_.strum1) || sf::Keyboard::isKeyPressed(settings_.strum2)))
			{
				dots[2].isHit = true;
				dots[2].sprite.setTexture(this->data_->assets.getTexture("EMPTYTEX"));
				this->score_ += 1 * this->combo_;
				this->combo_++;
				this->hitSound_.play();
			}
			if (Collision::scoreCollision(dots[3].sprite, this->fourthHitter_) && !dots[3].isHit && sf::Keyboard::isKeyPressed(settings_.hit4) && (sf::Keyboard::isKeyPressed(settings_.strum1) || sf::Keyboard::isKeyPressed(settings_.strum2)))
			{
				dots[3].isHit = true;
				dots[3].sprite.setTexture(this->data_->assets.getTexture("EMPTYTEX"));
				this->score_ += 1 * this->combo_;
				this->combo_++;
				this->hitSound_.play();
			}
		}
	}

	this->scoreText_.setString(std::to_string(this->score_));
	this->scoreText_.setOrigin(this->scoreText_.getGlobalBounds().width, this->scoreText_.getGlobalBounds().height);

	this->comboText_.setString(std::to_string(this->combo_) + "x");
	this->comboText_.setOrigin(this->comboText_.getGlobalBounds().width, this->comboText_.getGlobalBounds().height);

	if (this->combo_ > this->maxCombo_)
	{
		this->maxCombo_ = this->combo_;
	}
}

void GameState::genDots()
{
	for (auto i = 0; i < this->data_->songsData.getSong(this->songName_).chart.firstRow.size(); i++)
	{
		std::vector<Hitmarker> temp;

		if (this->data_->songsData.getSong(this->songName_).chart.firstRow[i] == true) {
			Hitmarker dot1(this->data_->assets.getTexture("1 dot"));
			dot1.sprite.setPosition(float(WIN_RES.x / 12), -dot1.sprite.getGlobalBounds().height);
			temp.emplace_back(dot1);
		}
		else
		{
			temp.emplace_back(Hitmarker(this->data_->assets.getTexture("EMPTYTEX")));
		}

		if (this->data_->songsData.getSong(this->songName_).chart.secondRow[i] == true) {
			Hitmarker dot2(this->data_->assets.getTexture("2 dot"));
			dot2.sprite.setPosition(float(WIN_RES.x / 4), -dot2.sprite.getGlobalBounds().height);
			temp.emplace_back(dot2);
		}
		else
		{
			temp.emplace_back(Hitmarker(this->data_->assets.getTexture("EMPTYTEX")));
		}

		if (this->data_->songsData.getSong(this->songName_).chart.thirdRow[i] == true) {
			Hitmarker dot3(this->data_->assets.getTexture("3 dot"));
			dot3.sprite.setPosition(float(WIN_RES.x * 5 / 12), -dot3.sprite.getGlobalBounds().height);
			temp.emplace_back(dot3);
		}
		else
		{
			temp.emplace_back(Hitmarker(this->data_->assets.getTexture("EMPTYTEX")));
		}

		if (this->data_->songsData.getSong(this->songName_).chart.fourthRow[0] == true) {
			Hitmarker dot4(this->data_->assets.getTexture("4 dot"));
			dot4.sprite.setPosition(float(WIN_RES.x * 7 / 12), -dot4.sprite.getGlobalBounds().height);
			temp.emplace_back(dot4);
		}
		else
		{
			temp.emplace_back(Hitmarker(this->data_->assets.getTexture("EMPTYTEX")));
		}

		this->chart_.emplace_back(temp);
	}
}


void GameState::drawDots()
{
	for (const auto& i : this->onScreen_)
	{
		for (const auto& j : i)
		{
			this->data_->window.draw(j.sprite);
		}
	}
}

void GameState::updateDots()
{
	if (this->songClock_.getElapsedTime().asSeconds() > this->data_->songsData.getSong(this->songName_).beatDuration && !this->chart_.empty())
	{
		this->onScreen_.push_back(this->chart_[0]);
		this->chart_.erase(this->chart_.begin());
		this->songClock_.restart();
	}

	for (auto& i : this->onScreen_)
	{
		for (auto& j : i)
		{
			j.sprite.move(0, scrollSpeed_);
			if (j.sprite.getPosition().y > WIN_RES.y)
			{
				this->onScreen_.erase(onScreen_.begin());
				break;
			}
		}
	}
}