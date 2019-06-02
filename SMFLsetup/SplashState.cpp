#include "pch.h"

SplashState::SplashState(std::shared_ptr<GameData> data) : data_(std::move(data))
{
	data_->assets.loadSound("TRANSITION", TRANSITION_SOUND_PATH);
	data_->assets.loadSound("APPLAUSE", APPLAUSE_SOUND_PATH);

	data_->assets.loadFont("MAIN", MAIN_FONT_PATH);

	data_->assets.loadTexture("splash bg", SPLASH_BG_PATH);
	data_->assets.loadTexture("menu bg", MENU_BG_PATH);
	data_->assets.loadTexture("options bg", OPTIONS_BG_PATH);
	data_->assets.loadTexture("key bg", KEY_BG_PATH);
	data_->assets.loadTexture("game bg", GAME_BG_PATH);
	data_->assets.loadTexture("paused bg", PAUSED_BG_PATH);
	data_->assets.loadTexture("end bg", END_BG_PATH);

	data_->assets.loadTexture("EMPTYTEX", EMPTY_TEX_PATH);
	data_->assets.loadTexture("dot 1", DOT1_PATH);
	data_->assets.loadTexture("dot 2", DOT2_PATH);
	data_->assets.loadTexture("dot 3", DOT3_PATH);
	data_->assets.loadTexture("dot 4", DOT4_PATH);
	data_->assets.loadTexture("dot hit", DOT_HIT_PATH);
	data_->assets.loadTexture("hit off", HIT_OFF_PATH);
	data_->assets.loadTexture("hit 1 on", HIT1_ON_PATH);
	data_->assets.loadTexture("hit 2 on", HIT2_ON_PATH);
	data_->assets.loadTexture("hit 3 on", HIT3_ON_PATH);
	data_->assets.loadTexture("hit 4 on", HIT4_ON_PATH);

	data_->transitionSound.setBuffer(data_->assets.getSound("TRANSITION"));
	data_->applauseSound.setBuffer(data_->assets.getSound("APPLAUSE"));
	data_->transitionSound.setVolume(50.f);
	data_->applauseSound.setVolume(35.f);

	bg_.setTexture(data_->assets.getTexture("splash bg"));
	data_->window.draw(bg_);
	data_->window.display();

	data_->backgroundMusic.openFromFile(SPLASH_MUSIC_PATH);
	data_->backgroundMusic.setLoop(true);
	data_->backgroundMusic.play();
}

void SplashState::handleInput()
{
	sf::Event event{};
	while (data_->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			data_->window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			data_->transitionSound.play();
			data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeDown)
		{
			data_->currentMusicVolume -= 10.0f;
			if (data_->currentMusicVolume < 0)
			{
				data_->currentMusicVolume = 0;
			}
			data_->backgroundMusic.setVolume(data_->currentMusicVolume);

		}
		if (event.type == sf::Event::KeyPressed && event.key.code == data_->settings.volumeUp)
		{
			data_->currentMusicVolume += 10.0f;
			if (data_->currentMusicVolume > 100)
			{
				data_->currentMusicVolume = 100;
			}
			data_->backgroundMusic.setVolume(data_->currentMusicVolume);
		}
	}
}

void SplashState::update(const float dt) {}

void SplashState::draw() {}