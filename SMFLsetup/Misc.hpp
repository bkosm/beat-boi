#pragma once

struct Settings
{
	sf::Keyboard::Key hit1, hit2, hit3, hit4, volumeUp, volumeDown;
	unsigned scrollSpeed{ 5 }, minumumScrollSpeed{ 0 };

	Settings();
	void resetSettings();
};

struct Hitmarker
{
	sf::Sprite sprite;
	bool isHit{};

	Hitmarker() = default;
	Hitmarker(const sf::Texture& texture, bool hit = false);
	bool hasEmptyTex() const;
};
