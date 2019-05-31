#include "pch.h"

Settings::Settings()
{
	hit1 = sf::Keyboard::Key::C;
	hit2 = sf::Keyboard::Key::V;
	hit3 = sf::Keyboard::Key::Period;
	hit4 = sf::Keyboard::Key::Slash;
	volumeUp = sf::Keyboard::Key::Equal;
	volumeDown = sf::Keyboard::Key::Hyphen;
}

void Settings::resetSettings()
{
	hit1 = sf::Keyboard::Key::C;
	hit2 = sf::Keyboard::Key::V;
	hit3 = sf::Keyboard::Key::Period;
	hit4 = sf::Keyboard::Key::Slash;
	volumeUp = sf::Keyboard::Key::Equal;
	volumeDown = sf::Keyboard::Key::Hyphen;
	scrollSpeed = 5;
}

Hitmarker::Hitmarker(const sf::Texture& texture, const bool hit)
{
	sprite.setTexture(texture);
	isHit = hit;
}

bool Hitmarker::hasEmptyTex() const
{
	return sprite.getTexture()->getSize().x == 1;
}