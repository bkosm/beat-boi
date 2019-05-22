#pragma once

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	static bool isSpriteClicked(const sf::Sprite& object, const sf::Mouse::Button& button, const sf::RenderWindow& window);
	static bool isTextClicked(const sf::Text& object, const sf::Mouse::Button& button, const sf::RenderWindow& window);
	static bool scoreCollision(const sf::Sprite& first, const sf::Sprite& second);
};