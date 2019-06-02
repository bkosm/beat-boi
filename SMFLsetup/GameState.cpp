#include "pch.h"

GameState::GameState(std::shared_ptr<GameData> data, std::string songName) :
	data_(std::move(data)),
	songName_(std::move(songName))
{
	genDots_();

	bg_.setTexture(data_->assets.getTexture("game bg"));

	firstHitter_.setPosition(float(WIN_RES.x * 0.1188), float(WIN_RES.y * 0.7));
	secondHitter_.setPosition(float(WIN_RES.x * 0.282), float(WIN_RES.y * 0.7));
	thirdHitter_.setPosition(float(WIN_RES.x * 0.445), float(WIN_RES.y * 0.7));
	fourthHitter_.setPosition(float(WIN_RES.x * 0.607), float(WIN_RES.y * 0.7));

	scoreText_.setFont(data_->assets.getFont("MAIN"));
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, scoreText_.getGlobalBounds().height);
	scoreText_.setPosition(float(WIN_RES.x * 0.995), float(WIN_RES.y * 0.028));
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setCharacterSize(15);

	comboText_.setFont(data_->assets.getFont("MAIN"));
	comboText_.setPosition(float(WIN_RES.x * 0.995), float(WIN_RES.y * 0.07));
	comboText_.setFillColor(sf::Color::White);
	comboText_.setCharacterSize(15);

	particles_.one.setEmitter(sf::Vector2f(firstHitter_.getPosition().x + firstHitter_.getGlobalBounds().width / 2, firstHitter_.getPosition().y + firstHitter_.getGlobalBounds().height / 2));
	particles_.two.setEmitter(sf::Vector2f(secondHitter_.getPosition().x + secondHitter_.getGlobalBounds().width / 2, secondHitter_.getPosition().y + secondHitter_.getGlobalBounds().height / 2));
	particles_.three.setEmitter(sf::Vector2f(thirdHitter_.getPosition().x + thirdHitter_.getGlobalBounds().width / 2, thirdHitter_.getPosition().y + thirdHitter_.getGlobalBounds().height / 2));
	particles_.four.setEmitter(sf::Vector2f(fourthHitter_.getPosition().x + fourthHitter_.getGlobalBounds().width / 2, fourthHitter_.getPosition().y + fourthHitter_.getGlobalBounds().height / 2));

	hitSound_.setBuffer(data_->songsData.getSong(songName_).hitSound);
	hitSound_.setVolume(data_->settings.hitSoundVolume);
	missSound_.setBuffer(data_->songsData.getSong(songName_).missSound);
	missSound_.setVolume(data_->settings.missSoundVolume);

	musicDuration_ = data_->songsData.getSong(songName_).music.getDuration().asSeconds();

	data_->songsData.getSong(songName_).music.play();

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
			data_->songsData.getSong(songName_).music.stop();
			data_->maschine.addState(std::make_unique<PauseState>(data_, songName_, score_, maxCombo_), true);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeDown)
		{
			data_->currentMusicVolume -= 10.0f;
			if (data_->currentMusicVolume < 0)
			{
				data_->currentMusicVolume = 0;
			}
			data_->songsData.getSong(songName_).music.setVolume(data_->currentMusicVolume);

		}
		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeUp)
		{
			data_->currentMusicVolume += 10.0f;
			if (data_->currentMusicVolume > 100)
			{
				data_->currentMusicVolume = 100;
			}
			data_->songsData.getSong(songName_).music.setVolume(data_->currentMusicVolume);
		}
	}
}

void GameState::update(const float dt)
{
	if (gameClock_.getElapsedTime().asSeconds() > musicDuration_)
	{
		score_ += maxCombo_ * data_->settings.scrollSpeed;
		data_->maschine.addState(std::make_unique<EndGameState>(data_, songName_, score_, maxCombo_), true);
	}

	animateHitmarkers_();
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
			if (dots[0].isHit && dots[1].isHit && dots[2].isHit && dots[3].isHit)
			{
				continue;
			}

			bool failed = false;
			int currentScore = 0;
			if (InputManager::scoreCollision(dots[0].sprite, firstHitter_) && !dots[0].isHit && !dots[0].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit1))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawOne = true;
				dots[0].isHit = true;
				dots[0].sprite.setTexture(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[0].sprite, firstHitter_) && dots[0].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit1))
			{
				failed = true;
				particles_.drawOne = false;
			}
			if (InputManager::scoreCollision(dots[1].sprite, secondHitter_) && !dots[1].isHit && !dots[1].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit2))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawTwo = true;
				dots[1].isHit = true;
				dots[1].sprite.setTexture(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[1].sprite, secondHitter_) && dots[1].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit2))
			{
				failed = true;
				particles_.drawTwo = false;
			}
			if (InputManager::scoreCollision(dots[2].sprite, thirdHitter_) && !dots[2].isHit && !dots[2].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit3))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawThree = true;
				dots[2].isHit = true;
				dots[2].sprite.setTexture(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[2].sprite, thirdHitter_) && dots[2].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit3))
			{
				failed = true;
				particles_.drawThree = false;
			}
			if (InputManager::scoreCollision(dots[3].sprite, fourthHitter_) && !dots[3].isHit && !dots[3].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit4))
			{
				combo_++;
				currentScore += 5 + combo_;
				particles_.drawFour = true;
				dots[3].isHit = true;
				dots[3].sprite.setTexture(data_->assets.getTexture("dot hit"));
			}
			else if (InputManager::scoreCollision(dots[3].sprite, fourthHitter_) && dots[3].hasEmptyTex() && sf::Keyboard::isKeyPressed(data_->settings.hit4))
			{
				failed = true;
				particles_.drawFour = false;
			}

			if (failed)
			{

				particles_.dontDraw();
				combo_ = 0;
				if (playMiss_)
				{
					missSound_.play();
				}
				playMiss_ = false;
			}
			else if (currentScore > 0 && particles_.isBeatValid())
			{
				hitSound_.play();
				playMiss_ = true;
				score_ += currentScore;
				break;
			}
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
	for (unsigned i = 0; i < data_->songsData.getSong(songName_).chart.firstRow.size(); i++)
	{
		std::vector<Hitmarker> temp;

		if (data_->songsData.getSong(songName_).chart.firstRow[i] == true) {
			Hitmarker dot1(data_->assets.getTexture("dot 1"));
			dot1.sprite.setPosition(float(WIN_RES.x * 0.1188), -dot1.sprite.getGlobalBounds().height);
			temp.emplace_back(dot1);
		}
		else
		{
			Hitmarker dot1(this->data_->assets.getTexture("EMPTYTEX"), true);
			dot1.sprite.setPosition(float(WIN_RES.x * 0.1188), -dot1.sprite.getGlobalBounds().height);
			temp.emplace_back(dot1);
		}

		if (data_->songsData.getSong(songName_).chart.secondRow[i] == true) {
			Hitmarker dot2(data_->assets.getTexture("dot 2"));
			dot2.sprite.setPosition(float(WIN_RES.x * 0.282), -dot2.sprite.getGlobalBounds().height);
			temp.emplace_back(dot2);
		}
		else
		{
			Hitmarker dot2(this->data_->assets.getTexture("EMPTYTEX"), true);
			dot2.sprite.setPosition(float(WIN_RES.x * 0.282), -dot2.sprite.getGlobalBounds().height);
			temp.emplace_back(dot2);
		}

		if (data_->songsData.getSong(songName_).chart.thirdRow[i] == true) {
			Hitmarker dot3(data_->assets.getTexture("dot 3"));
			dot3.sprite.setPosition(float(WIN_RES.x * 0.445), -dot3.sprite.getGlobalBounds().height);
			temp.emplace_back(dot3);
		}
		else
		{
			Hitmarker dot3(this->data_->assets.getTexture("EMPTYTEX"), true);
			dot3.sprite.setPosition(float(WIN_RES.x * 0.445), -dot3.sprite.getGlobalBounds().height);
			temp.emplace_back(dot3);
		}

		if (data_->songsData.getSong(songName_).chart.fourthRow[i] == true) {
			Hitmarker dot4(data_->assets.getTexture("dot 4"));
			dot4.sprite.setPosition(float(WIN_RES.x * 0.607), -dot4.sprite.getGlobalBounds().height);
			temp.emplace_back(dot4);
		}
		else
		{
			Hitmarker dot4(this->data_->assets.getTexture("EMPTYTEX"), true);
			dot4.sprite.setPosition(float(WIN_RES.x * 0.607), -dot4.sprite.getGlobalBounds().height);
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

void GameState::updateDots_(const float dt)
{
	timeAccumulator_ += dt;
	if (songClock_.getElapsedTime().asSeconds() + timeAccumulator_ > data_->songsData.getSong(songName_).beatDuration && !chart_.empty())
	{
		onScreen_.emplace_back(chart_[0]);
		chart_.erase(chart_.begin());
		timeAccumulator_ = 0.0f;
		songClock_.restart();
	}

	for (auto& i : onScreen_)
	{
		for (auto& j : i)
		{
			j.sprite.move(0, data_->settings.scrollSpeed);
			if (j.sprite.getPosition().y > firstHitter_.getPosition().y + firstHitter_.getGlobalBounds().height)
			{
				for (const auto& dot : *onScreen_.begin())
				{
					if (!dot.isHit)
					{
						combo_ = 0;
						particles_.dontDraw();
						if (playMiss_)
						{
							missSound_.play();
						}
						playMiss_ = false;
						break;
					}
				}
				onScreen_.erase(onScreen_.begin());
				break;
			}
		}
	}
}

void GameState::animateHitmarkers_()
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