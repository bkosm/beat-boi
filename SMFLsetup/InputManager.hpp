#pragma once

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	static bool isShapeClicked(const sf::Shape& object, const sf::Mouse::Button& button, const sf::RenderWindow& window);
	static bool scoreCollision(const sf::Sprite& first, const sf::Sprite& second);
};