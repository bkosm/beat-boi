#include "pch.h"
#include "Game.h"
#include "SplashState.h"
#include <random>

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

void DancerSprite::animate(GameDataRef& gameData, const std::string& firstTextureName,
	const std::string& secondTextureName, const float animationDuration)
{
	if (this->clock.getElapsedTime().asSeconds() > animationDuration)
	{
		if (this->frame.left > int(gameData->assets.getTexture(firstTextureName).getSize().x * 3 / 4))
		{
			this->frame.left = 0;
			if (isFirst)
			{
				this->sprite.setTexture(gameData->assets.getTexture(secondTextureName));
				isFirst = false;
			}
			else
			{
				this->sprite.setTexture(gameData->assets.getTexture(firstTextureName));
				isFirst = true;
			}
		}

		this->sprite.setTextureRect(this->frame);
		this->frame.left += BOI_ANIMATION_HORIZONTAL;
		this->clock.restart();
	}
}