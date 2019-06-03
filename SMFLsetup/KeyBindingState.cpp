#include "pch.h"

KeyBindingState::KeyBindingState(std::shared_ptr<GameData> data, std::string songName) : 
	data_(std::move(data)),
	songName_(std::move(songName))
{
	bg_.setTexture(data_->assets.getTexture("key bg"));

	speedText_.setFont(data_->assets.getFont("MAIN"));
	speedText_.setCharacterSize(35);
	speedText_.setFillColor(sf::Color::Black);
	speedText_.setPosition(float(data_->window.getSize().x * 0.562), float(data_->window.getSize().y * 0.82));

	data_->songsData.getMusic().setVolume(data_->settings.currentMusicVolume);
}

void KeyBindingState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			data_->window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			data_->transitionSound.play();
			data_->maschine.removeState();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			data_->settings.scrollSpeed--;
			if (data_->settings.scrollSpeed < data_->settings.minumumScrollSpeed)
			{
				data_->settings.scrollSpeed = data_->settings.minumumScrollSpeed;
			}
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			data_->settings.scrollSpeed++;
			if (data_->settings.scrollSpeed > 15)
			{
				data_->settings.scrollSpeed = 15;
			}
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
		{
			data_->songsData.getMusic().stop();
			data_->transitionSound.play();
			data_->songsData.unloadSong();
			data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
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

void KeyBindingState::update(const float dt)
{
	speedText_.setString(std::to_string(data_->settings.scrollSpeed));
	speedText_.setOrigin(speedText_.getGlobalBounds().width / 2, 0);
}

void KeyBindingState::draw()
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(speedText_);
	data_->window.display();
}
