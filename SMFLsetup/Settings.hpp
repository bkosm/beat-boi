#pragma once

class Settings
{
public:
	Settings();
	void resetSettings();
	
	sf::Keyboard::Key hit1, hit2, hit3, hit4, volumeUp, volumeDown;

	unsigned scrollSpeed{ 5 }, minumumScrollSpeed{ 0 };
	float hitSoundVolume{ 9.0f }, missSoundVolume{ 10.0f }, currentMusicVolume{ 100.0f }, transitionVolume{ 50.0f }, applauseVolume{ 35.0f };
};