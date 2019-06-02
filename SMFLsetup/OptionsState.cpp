#include "pch.h"

OptionsState::OptionsState(std::shared_ptr<GameData> data, std::string songName) :
	data_(std::move(data)),
	songName_(std::move(songName))
{
	bg_.setTexture(data_->assets.getTexture("options bg"));

	data_->settings.minumumScrollSpeed = unsigned(data_->songsData.getSong().bpm / 18 + 1);
	data_->settings.scrollSpeed = data_->settings.minumumScrollSpeed;

	play_.setSize(sf::Vector2f(400, 25));
	play_.setFillColor(sf::Color::Transparent);
	play_.setPosition(float(WIN_RES.x / 2 - play_.getGlobalBounds().width / 2), float(WIN_RES.y / 2 - 2 * play_.getGlobalBounds().height));

	viewKeys_.setSize(sf::Vector2f(400, 25));
	viewKeys_.setFillColor(sf::Color::Transparent);
	viewKeys_.setPosition(float(WIN_RES.x / 2 - viewKeys_.getGlobalBounds().width / 2), float(WIN_RES.y / 2));

	return_.setSize(sf::Vector2f(400, 25));
	return_.setFillColor(sf::Color::Transparent);
	return_.setPosition(float(WIN_RES.x / 2 - return_.getGlobalBounds().width / 2), float(WIN_RES.y / 2 + 2 * return_.getGlobalBounds().height));

	data_->songsData.getSong().music.setVolume(data_->currentMusicVolume);
	data_->songsData.getSong().music.play();
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

		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeDown)
		{
			data_->currentMusicVolume -= 10.0f;
			if (data_->currentMusicVolume < 0)
			{
				data_->currentMusicVolume = 0;
			}
			data_->songsData.getSong().music.setVolume(data_->currentMusicVolume);

		}
		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeUp)
		{
			data_->currentMusicVolume += 10.0f;
			if (data_->currentMusicVolume > 100)
			{
				data_->currentMusicVolume = 100;
			}
			data_->songsData.getSong().music.setVolume(data_->currentMusicVolume);
		}
	}

	if (InputManager::isShapeClicked(play_, sf::Mouse::Left, data_->window) && !clicked_ || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !clicked_)
	{
		clicked_ = true;
		data_->songsData.getSong().music.stop();
		data_->transitionSound.play();
		data_->maschine.removeState();
		data_->maschine.addState(std::make_unique<GameState>(data_, songName_), true);
	}
	if (InputManager::isShapeClicked(viewKeys_, sf::Mouse::Left, data_->window))
	{
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<KeyBindingState>(data_, songName_), false);
	}
	if (InputManager::isShapeClicked(return_, sf::Mouse::Left, data_->window))
	{
		data_->songsData.getSong().music.stop();
		data_->transitionSound.play();
		data_->maschine.removeState();
		data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
	}
}

void OptionsState::update(const float dt) {}

void OptionsState::draw()
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(play_);
	data_->window.draw(viewKeys_);
	data_->window.draw(return_);
	data_->window.display();
}
