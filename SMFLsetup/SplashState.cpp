#include "pch.h"

SplashState::SplashState(GameDataRef data) : data_(std::move(data))
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
	data_->assets.loadTexture("hit off", HIT_OFF_PATH);
	data_->assets.loadTexture("hit 1 on", HIT1_ON_PATH);
	data_->assets.loadTexture("hit 2 on", HIT2_ON_PATH);
	data_->assets.loadTexture("hit 3 on", HIT3_ON_PATH);
	data_->assets.loadTexture("hit 4 on", HIT4_ON_PATH);

	data_->transitionSound.setBuffer(data_->assets.getSound("TRANSITION"));
	data_->applauseSound.setBuffer(data_->assets.getSound("APPLAUSE"));
	data_->transitionSound.setVolume(50.f);
	data_->applauseSound.setVolume(50.f);

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
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		data_->backgroundMusic.stop();
		data_->songsData.loadSong("popstars");
		data_->maschine.addState(std::make_unique<GameState>(data_, "popstars"), true);
	}
}

void SplashState::update(float dt)
{
}

void SplashState::draw(float dt)
{
}