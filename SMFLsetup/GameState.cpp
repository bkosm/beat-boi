#include "pch.h"

GameState::GameState(std::shared_ptr<GameData> data, std::string songName) :
	data_(std::move(data)),
	sounds_(data_->songsData.getHitSound(), data_->settings.hitSoundVolume, data_->songsData.getMissSound(), data_->settings.missSoundVolume),
	songName_(std::move(songName))
{
	genDots_();

	bg_.setTexture(data_->assets.getTexture("game bg"));

	firstHitter_.setPosition(float(data_->window.getSize().x * 0.1188), float(data_->window.getSize().y * 0.7));
	secondHitter_.setPosition(float(data_->window.getSize().x * 0.282), float(data_->window.getSize().y * 0.7));
	thirdHitter_.setPosition(float(data_->window.getSize().x * 0.445), float(data_->window.getSize().y * 0.7));
	fourthHitter_.setPosition(float(data_->window.getSize().x * 0.607), float(data_->window.getSize().y * 0.7));

	scoreText_.setFont(data_->assets.getFont("MAIN"));
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, scoreText_.getGlobalBounds().height);
	scoreText_.setPosition(float(data_->window.getSize().x * 0.995), float(data_->window.getSize().y * 0.028));
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setCharacterSize(15);

	comboText_.setFont(data_->assets.getFont("MAIN"));
	comboText_.setPosition(float(data_->window.getSize().x * 0.995), float(data_->window.getSize().y * 0.07));
	comboText_.setFillColor(sf::Color::White);
	comboText_.setCharacterSize(15);

	particles_.one.setEmitter(sf::Vector2f(firstHitter_.getPosition().x + firstHitter_.getGlobalBounds().width / 2, firstHitter_.getPosition().y + firstHitter_.getGlobalBounds().height / 2));
	particles_.two.setEmitter(sf::Vector2f(secondHitter_.getPosition().x + secondHitter_.getGlobalBounds().width / 2, secondHitter_.getPosition().y + secondHitter_.getGlobalBounds().height / 2));
	particles_.three.setEmitter(sf::Vector2f(thirdHitter_.getPosition().x + thirdHitter_.getGlobalBounds().width / 2, thirdHitter_.getPosition().y + thirdHitter_.getGlobalBounds().height / 2));
	particles_.four.setEmitter(sf::Vector2f(fourthHitter_.getPosition().x + fourthHitter_.getGlobalBounds().width / 2, fourthHitter_.getPosition().y + fourthHitter_.getGlobalBounds().height / 2));

	musicDuration_ = data_->songsData.getMusic().getDuration().asSeconds();

	data_->songsData.getMusic().play();

	gameClock_.restart();
	songClock_.restart();
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
			data_->songsData.getMusic().stop();
			data_->maschine.removeState();
			data_->maschine.addState(std::make_unique<PauseState>(data_, songName_, score_, maxCombo_), true);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeDown)
		{
			data_->settings.currentMusicVolume -= 10.0f;
			if (data_->settings.currentMusicVolume < 0)
			{
				data_->settings.currentMusicVolume = 0;
			}
			data_->songsData.getMusic().setVolume(data_->settings.currentMusicVolume);

		}
		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeUp)
		{
			data_->settings.currentMusicVolume += 10.0f;
			if (data_->settings.currentMusicVolume > 100)
			{
				data_->settings.currentMusicVolume = 100;
			}
			data_->songsData.getMusic().setVolume(data_->settings.currentMusicVolume);
		}
	}
}

void GameState::update(const float dt)
{
	if (gameClock_.getElapsedTime().asSeconds() > musicDuration_)
	{
		score_ += maxCombo_ * data_->settings.scrollSpeed;
		data_->maschine.removeState();
		data_->maschine.addState(std::make_unique<EndGameState>(data_, songName_, score_, maxCombo_), true);
	}

	animateHitters_();
	updateDots_(dt);
	updateScore_();

	particles_.updateAll();
}

void GameState::draw()
{
	data_->window.clear();

	data_->window.draw(bg_);
	data_->window.draw(scoreText_);
	data_->window.draw(comboText_);
	data_->window.draw(firstHitter_);
	data_->window.draw(secondHitter_);
	data_->window.draw(fourthHitter_);
	data_->window.draw(thirdHitter_);
	drawDots_();
	particles_.draw(data_->window);

	data_->window.display();
}

void GameState::updateScore_()
{
	if (!chart_.empty())
	{
		for (auto& dots : onScreen_)
		{
			if (dots[0].isHit() && dots[1].isHit() && dots[2].isHit() && dots[3].isHit())
			{
				continue;
			}

			bool failed = false;
			int currentScore = 0;

			if (InputManager::scoreCollision(dots[0].getSprite(), firstHitter_) && !dots[0].isHit() && !dots[0].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit1))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawOne = true;
				dots[0].setHit(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[0].getSprite(), firstHitter_) && dots[0].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit1))
			{
				failed = true;
				particles_.drawOne = false;
			}

			if (InputManager::scoreCollision(dots[1].getSprite(), secondHitter_) && !dots[1].isHit() && !dots[1].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit2))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawTwo = true;
				dots[1].setHit(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[1].getSprite(), secondHitter_) && dots[1].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit2))
			{
				failed = true;
				particles_.drawTwo = false;
			}

			if (InputManager::scoreCollision(dots[2].getSprite(), thirdHitter_) && !dots[2].isHit() && !dots[2].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit3))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawThree = true;
				dots[2].setHit(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[2].getSprite(), thirdHitter_) && dots[2].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit3))
			{
				failed = true;
				particles_.drawThree = false;
			}

			if (InputManager::scoreCollision(dots[3].getSprite(), fourthHitter_) && !dots[3].isHit() && !dots[3].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit4))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawFour = true;
				dots[3].setHit(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[3].getSprite(), fourthHitter_) && dots[3].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit4))
			{
				failed = true;
				particles_.drawFour = false;
			}

			if (failed)
			{

				sounds_.playMissSound();
				particles_.dontDraw();
				combo_ = 0;
			}
			else if (currentScore > 0 && particles_.isBeatValid())
			{
				sounds_.playHitSound();
				sounds_.unblockMissSound();
				score_ += currentScore;
				break;
			}
		}
	}

	scoreText_.setString(std::to_string(score_));
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, scoreText_.getGlobalBounds().height);

	comboText_.setString(std::to_string(combo_) + "x");
	comboText_.setOrigin(comboText_.getGlobalBounds().width, comboText_.getGlobalBounds().height);

	if (combo_ > maxCombo_) maxCombo_ = combo_;
}

void GameState::genDots_()
{
	Hitmarker tempHit1(data_->assets.getTexture("dot 1")), tempHit2(data_->assets.getTexture("dot 1")), tempHit3(data_->assets.getTexture("dot 3")), tempHit4(data_->assets.getTexture("dot 4"));
	tempHit1.setPosition(float(data_->window.getSize().x * 0.1188), -tempHit1.getSprite().getGlobalBounds().height);
	tempHit2.setPosition(float(data_->window.getSize().x * 0.282), -tempHit2.getSprite().getGlobalBounds().height);
	tempHit3.setPosition(float(data_->window.getSize().x * 0.445), -tempHit3.getSprite().getGlobalBounds().height);
	tempHit4.setPosition(float(data_->window.getSize().x * 0.607), -tempHit4.getSprite().getGlobalBounds().height);

	for (unsigned i = 0; i < data_->songsData.chartLength(); i++)
	{
		std::vector<Hitmarker> tempVec;

		if (data_->songsData.getChart().firstRow[i] == true) {
			tempHit1.setTexture(data_->assets.getTexture("dot 1"));
			tempVec.push_back(tempHit1);
		}
		else
		{
			tempHit1.setHit(this->data_->assets.getTexture("EMPTYTEX"));
			tempVec.push_back(tempHit1);
			tempHit1.reset();
		}

		if (data_->songsData.getChart().secondRow[i] == true) {
			tempHit2.setTexture(data_->assets.getTexture("dot 2"));
			tempVec.push_back(tempHit2);
		}
		else
		{
			tempHit2.setHit(this->data_->assets.getTexture("EMPTYTEX"));
			tempVec.push_back(tempHit2);
			tempHit2.reset();
		}

		if (data_->songsData.getChart().thirdRow[i] == true) {
			tempHit3.setTexture(data_->assets.getTexture("dot 3"));
			tempVec.push_back(tempHit3);
		}
		else
		{
			tempHit3.setHit(this->data_->assets.getTexture("EMPTYTEX"));
			tempVec.push_back(tempHit3);
			tempHit3.reset();
		}

		if (data_->songsData.getChart().fourthRow[i] == true) {
			tempHit4.setTexture(data_->assets.getTexture("dot 4"));
			tempVec.push_back(tempHit4);
		}
		else
		{
			tempHit4.setHit(this->data_->assets.getTexture("EMPTYTEX"));
			tempVec.push_back(tempHit4);
			tempHit4.reset();
		}

		chart_.emplace_back(tempVec);
	}
}


void GameState::drawDots_()
{
	for (const auto& i : onScreen_)
	{
		for (const auto& j : i)
		{
			data_->window.draw(j.getSprite());
		}
	}
}

void GameState::updateDots_(const float dt)
{
	timeAccumulator_ += dt;
	if (songClock_.getElapsedTime().asSeconds() + timeAccumulator_ > data_->songsData.getBeatDuration() && !chart_.empty())
	{
		timeAccumulator_ = 0.0f;
		onScreen_.emplace_back(chart_[0]);
		chart_.erase(chart_.begin());
		songClock_.restart();
	}

	for (auto& i : onScreen_)
	{
		for (auto& j : i)
		{
			j.getSprite().move(0, data_->settings.scrollSpeed);
			if (j.getSprite().getPosition().y > firstHitter_.getPosition().y + firstHitter_.getGlobalBounds().height)
			{
				for (const auto& dot : *onScreen_.begin())
				{
					if (!dot.isHit())
					{
						sounds_.playMissSound();
						particles_.dontDraw();
						combo_ = 0;
						break;
					}
				}
				onScreen_.erase(onScreen_.begin());
				break;
			}
		}
	}
}

void GameState::animateHitters_()
{
	if (sf::Keyboard::isKeyPressed(data_->settings.hit1))
	{
		firstHitter_.setTexture(data_->assets.getTexture("hit 1 on"));
	}
	else
	{
		firstHitter_.setTexture(data_->assets.getTexture("hit off"));
	}

	if (sf::Keyboard::isKeyPressed(data_->settings.hit2))
	{
		secondHitter_.setTexture(data_->assets.getTexture("hit 2 on"));
	}
	else
	{
		secondHitter_.setTexture(data_->assets.getTexture("hit off"));
	}

	if (sf::Keyboard::isKeyPressed(data_->settings.hit3))
	{
		thirdHitter_.setTexture(data_->assets.getTexture("hit 3 on"));
	}
	else
	{
		thirdHitter_.setTexture(data_->assets.getTexture("hit off"));
	}

	if (sf::Keyboard::isKeyPressed(data_->settings.hit4))
	{
		fourthHitter_.setTexture(data_->assets.getTexture("hit 4 on"));
	}
	else
	{
		fourthHitter_.setTexture(data_->assets.getTexture("hit off"));
	}
}