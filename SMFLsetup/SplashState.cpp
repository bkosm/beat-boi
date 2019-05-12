#include "pch.h"
#include "GlobalConstants.hpp"
#include "MainMenuState.hpp"
#include "SplashState.h"

SplashState::SplashState(GameDataRef data) : data_(std::move(data)) {}

void SplashState::init()
{
	this->data_->assets.loadTexture("SPLASHBACKGROUND", SPLASH_BG_PATH);
	this->data_->assets.loadTexture("MENUBACKGROUND", MENU_BG_PATH);

	this->data_->assets.loadTexture("BREAKDANCEBOI1", INTRO_BOI_1_SPRITE_PATH);
	this->data_->assets.loadTexture("BREAKDANCEBOI2", INTRO_BOI_2_SPRITE_PATH);
	this->data_->assets.loadTexture("HANDSUPBOI1", SONG1_BOI_1_SPRITE_PATH);
	this->data_->assets.loadTexture("HANDSUPBOI2", SONG1_BOI_2_SPRITE_PATH);

	this->data_->assets.loadTexture("1 hit off", HIT1_OFF_PATH);
	this->data_->assets.loadTexture("1 hit on", HIT1_ON_PATH);
	this->data_->assets.loadTexture("2 hit off", HIT2_OFF_PATH);
	this->data_->assets.loadTexture("2 hit on", HIT2_ON_PATH);
	this->data_->assets.loadTexture("3 hit off", HIT3_OFF_PATH);
	this->data_->assets.loadTexture("3 hit on", HIT3_ON_PATH);
	this->data_->assets.loadTexture("4 hit off", HIT4_OFF_PATH);
	this->data_->assets.loadTexture("4 hit on", HIT4_ON_PATH);

	this->data_->assets.loadTexture("1 dot", DOT1_PATH);
	this->data_->assets.loadTexture("2 dot", DOT2_PATH);
	this->data_->assets.loadTexture("3 dot", DOT3_PATH);
	this->data_->assets.loadTexture("4 dot", DOT4_PATH);


	this->data_->assets.loadTexture("EMPTYTEX", EMPTY_TEX_PATH);
	this->data_->assets.loadFont("AIRFONT", AIR_FONT_PATH);
	this->data_->assets.loadSound("TRANSITION", TRANSITION_SOUND_PATH);
	this->data_->assets.loadSound("HITSOUND", HIT_SOUND_PATH);

	this->background_.setTexture(this->data_->assets.getTexture("SPLASHBACKGROUND"));

	this->dancer_.sprite.setTexture(this->data_->assets.getTexture("BREAKDANCEBOI1"));
	this->dancer_.sprite.setPosition(float(WIN_RES.x / 2) - this->dancer_.sprite.getGlobalBounds().width / 2, float(WIN_RES.y * 2 / 5));

	this->data_->backgroundMusic.openFromFile(SPLASH_MUSIC_PATH);
	this->data_->backgroundMusic.setLoop(true);
	this->data_->backgroundMusic.play();
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
	}
}

void SplashState::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->data_->maschine.addState(std::make_unique<MainMenuState>(this->data_), false);
	}

	this->dancer_.animate(this->data_, "BREAKDANCEBOI1", "BREAKDANCEBOI2", SPLASH_ANIMATION_DURATION);
}

void SplashState::draw(float dt)
{
	data_->window.clear(sf::Color::Magenta);
	data_->window.draw(background_);
	data_->window.draw(dancer_.sprite);
	data_->window.display();
}