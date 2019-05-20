#include "pch.h"

MainMenuState::MainMenuState(GameDataRef data) : data_(std::move(data)) {}

void MainMenuState::init()
{
	background_.setTexture(data_->assets.getTexture("MENUBACKGROUND"));

	firstSongText_.setPosition(float(WIN_RES.x / 24), float(WIN_RES.y / 6));
	firstSongText_.setString("SONG 1\nPOPSTARS\nYGLisiu Remix");
	firstSongText_.setFont(data_->assets.getFont("MAIN"));
	firstSongText_.setFillColor(sf::Color::Black);
	firstSongText_.setCharacterSize(20);

	sound_.setBuffer(data_->assets.getSound("TRANSITION"));
	sound_.play();

	data_->songsData.unloadSongs();
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
	if (data_->input.isTextClicked(firstSongText_, sf::Mouse::Left, data_->window))
	{

		data_->songsData.loadSong(POPSTARS_SONG);
		data_->backgroundMusic.stop();
		data_->maschine.addState(std::make_unique<GameState>(data_, POPSTARS_SONG), true);
	}
}

void MainMenuState::draw(float dt)
{
	data_->window.clear(sf::Color::Magenta);
	data_->window.draw(background_);
	data_->window.draw(firstSongText_);
	data_->window.display();
}