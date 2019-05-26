#include "pch.h"

Settings::Settings()
{
	hit1 = sf::Keyboard::Key::Z;
	hit2 = sf::Keyboard::Key::X;
	hit3 = sf::Keyboard::Key::C;
	hit4 = sf::Keyboard::Key::V;
	volumeUp = sf::Keyboard::Key::Equal;
	volumeDown = sf::Keyboard::Key::Hyphen;
	speedUp = sf::Keyboard::Key::RBracket;
	speedDown = sf::Keyboard::Key::LBracket;
}

void Settings::resetKeyBindings()
{
	hit1 = sf::Keyboard::Key::Z;
	hit2 = sf::Keyboard::Key::X;
	hit3 = sf::Keyboard::Key::C;
	hit4 = sf::Keyboard::Key::V;
	volumeUp = sf::Keyboard::Key::Equal;
	volumeDown = sf::Keyboard::Key::Hyphen;
	speedUp = sf::Keyboard::Key::RBracket;
	speedDown = sf::Keyboard::Key::LBracket;
}

Hitmarker::Hitmarker(const sf::Texture& texture, bool hit)
{
	sprite.setTexture(texture);
	isHit = hit;
}

bool Hitmarker::hasEmptyTex() const
{
	if (sprite.getTexture()->getSize().x == 1)
	{
		return true;
	}
	return false;
}

Game::Game(unsigned width, unsigned height, const std::string& title)
{
	data_->window.create(sf::VideoMode(width, height), title, sf::Style::Close);
	data_->maschine.addState(std::unique_ptr<State>(std::make_unique<SplashState>(data_)), false);

	run();
}

int Game::randInt(const int min, const int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

void Game::run() const
{
	float accumulator = 0.f, currentTime = clock_.getElapsedTime().asSeconds();

	while (data_->window.isOpen())
	{
		data_->maschine.processStateChanges();
		const float newTime = clock_.getElapsedTime().asSeconds();
		float frameTime = newTime - currentTime;

		if (frameTime > 0.25f) frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt_)
		{
			data_->maschine.getActiveState()->handleInput();
			data_->maschine.getActiveState()->update(dt_);

			accumulator -= dt_;
		}
		const float interpolation = accumulator / dt_;
		data_->maschine.getActiveState()->draw(interpolation);
	}
}
