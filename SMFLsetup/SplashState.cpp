#include "pch.h"

SplashState::SplashState(GameDataRef data) : data_(std::move(data)) {}

void SplashState::init()
{
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

	data_->transitionSound.setBuffer(data_->assets.getSound("TRANSITION"));
	data_->transitionSound.setVolume(50.f);

	dancer_.sprite.setTexture(data_->assets.getTexture("BREAKDANCEBOI1"));
	dancer_.sprite.setPosition(float(WIN_RES.x / 2) - dancer_.sprite.getGlobalBounds().width / 2, float(WIN_RES.y * 2 / 5));

	title_.setFont(data_->assets.getFont("MAIN"));
	title_.setCharacterSize(90);
	title_.setOutlineThickness(2.f);
	title_.setFillColor(sf::Color::Black);
	title_.setOutlineColor(sf::Color::White);
	title_.setString("BeatBoi");
	title_.setPosition(float(WIN_RES.x / 2) - title_.getGlobalBounds().width / 2, float(WIN_RES.y * 0.1));

	enter_.setFont(data_->assets.getFont("MAIN"));
	enter_.setCharacterSize(40);
	enter_.setOutlineThickness(1.f);
	enter_.setFillColor(sf::Color::White);
	enter_.setOutlineColor(sf::Color::Black);
	enter_.setString("Press Space to Play");
	enter_.setPosition(float(WIN_RES.x / 2) - enter_.getGlobalBounds().width / 2, float(WIN_RES.y * 0.8));

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
			data_->maschine.addState(std::make_unique<MainMenuState>(data_), false);
		}
	}
}

void SplashState::update(float dt)
{
	if (data_->backgroundMusic.getStatus() == sf::Music::Stopped)
	{
		data_->backgroundMusic.play();
	}
	dancer_.animate(this->data_, "BREAKDANCEBOI1", "BREAKDANCEBOI2", SPLASH_ANIMATION_DURATION * 0.25f);
}

void SplashState::draw(float dt)
{
	data_->window.clear(BG_COLOR);
	data_->window.draw(title_);
	data_->window.draw(enter_);
	data_->window.draw(dancer_.sprite);
	data_->window.display();
}