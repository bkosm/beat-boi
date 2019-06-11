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
	scrollSpeed = 3;
	hitSoundVolume = 8.f;
	missSoundVolume = 7.f;
	transitionVolume = 50.0f;
	applauseVolume = 35.0f;
}