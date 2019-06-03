#include "pch.h"

Hitmarker::Hitmarker(const sf::Texture& texture, const bool hit)
{
	sprite_.setTexture(texture);
	isHit_ = hit;
}

const sf::Sprite& Hitmarker::getSprite() const
{
	return sprite_;
}

sf::Sprite& Hitmarker::getSprite()
{
	return sprite_;
}

bool Hitmarker::hasEmptyTex() const
{
	return sprite_.getTexture()->getSize().x == 1;
}

bool Hitmarker::isHit() const
{
	return isHit_;
}

void Hitmarker::setHit(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
	isHit_ = true;
}

void Hitmarker::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

void Hitmarker::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

void Hitmarker::reset()
{
	isHit_ = false;
}
