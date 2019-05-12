#include "pch.h"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include <utility>

MainMenuState::MainMenuState(GameDataRef data) : data_(std::move(data)) {}

void MainMenuState::init()
{
	this->background_.setTexture(this->data_->assets.getTexture("MENUBACKGROUND"));

	this->firstSongText_.setPosition(float(WIN_RES.x / 24), float(WIN_RES.y / 6));
	this->firstSongText_.setString("SONG 1\nPOPSTARS - YGLisiu Remix");
	this->firstSongText_.setFont(this->data_->assets.getFont("AIRFONT"));
	this->firstSongText_.setFillColor(sf::Color::Black);
	this->firstSongText_.setCharacterSize(40);

	this->sound_.setBuffer(this->data_->assets.getSound("TRANSITION"));
	this->sound_.play();

	this->data_->songsData.unloadSongs();
}

void MainMenuState::handleInput()
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

void MainMenuState::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || this->data_->input.isTextClicked(this->firstSongText_, sf::Mouse::Left, this->data_->window))
	{

		this->data_->songsData.loadSong(POPSTARS_SONG);
		this->data_->backgroundMusic.stop();
		this->data_->maschine.addState(std::make_unique<GameState>(this->data_, POPSTARS_SONG), true);
	}
}

void MainMenuState::draw(float dt)
{
	data_->window.clear(sf::Color::Magenta);
	data_->window.draw(background_);
	data_->window.draw(firstSongText_);
	data_->window.display();
}