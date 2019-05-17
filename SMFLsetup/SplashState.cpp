#include "pch.h"
#include "GlobalConstants.hpp"
#include "MainMenuState.hpp"
#include "SplashState.h"

SplashState::SplashState(GameDataRef data) : data_(std::move(data)) {}

void SplashState::init()
{
	data_->assets.loadTexture("SPLASHBACKGROUND", SPLASH_BG_PATH);
	data_->assets.loadTexture("MENUBACKGROUND", MENU_BG_PATH);

	data_->assets.loadTexture("BREAKDANCEBOI1", INTRO_BOI_1_SPRITE_PATH);
	data_->assets.loadTexture("BREAKDANCEBOI2", INTRO_BOI_2_SPRITE_PATH);
	data_->assets.loadTexture("HANDSUPBOI1", SONG1_BOI_1_SPRITE_PATH);
	data_->assets.loadTexture("HANDSUPBOI2", SONG1_BOI_2_SPRITE_PATH);

	data_->assets.loadTexture("hit on", HIT_ON_PATH);
	data_->assets.loadTexture("hit off", HIT_OFF_PATH);

	data_->assets.loadTexture("dot", DOT_PATH);


	data_->assets.loadTexture("EMPTYTEX", EMPTY_TEX_PATH);
	data_->assets.loadFont("MAIN", MAIN_FONT_PATH);
	data_->assets.loadSound("TRANSITION", TRANSITION_SOUND_PATH);
	data_->assets.loadSound("HITSOUND", HIT_SOUND_PATH);
	data_->assets.loadSound("KICK", KICK_PATH);
	data_->assets.loadSound("CLAP", CLAP_PATH);
	data_->assets.loadSound("HAT", HAT_PATH);
	data_->assets.loadSound("PERC", PERC_PATH);

	background_.setTexture(data_->assets.getTexture("SPLASHBACKGROUND"));

	dancer_.sprite.setTexture(data_->assets.getTexture("BREAKDANCEBOI1"));
	dancer_.sprite.setPosition(float(WIN_RES.x / 2) - dancer_.sprite.getGlobalBounds().width / 2, float(WIN_RES.y * 2 / 5));

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

		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			data_->maschine.addState(std::make_unique<MainMenuState>(data_), false);
		}
	}
}

void SplashState::update(float dt)
{
	dancer_.animate(this->data_, "BREAKDANCEBOI1", "BREAKDANCEBOI2", SPLASH_ANIMATION_DURATION);
}

void SplashState::draw(float dt)
{
	data_->window.clear(sf::Color::Magenta);
	data_->window.draw(background_);
	data_->window.draw(dancer_.sprite);
	data_->window.display();
}