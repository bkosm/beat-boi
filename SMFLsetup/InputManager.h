#pragma once
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	bool isSpriteClicked(const sf::Sprite& object, const sf::Mouse::Button& button, const sf::RenderWindow& window) const;
	bool isTextClicked(const sf::Text& object, const sf::Mouse::Button& button, const sf::RenderWindow& window) const;
	sf::Vector2i getMousePosition(const sf::RenderWindow& window) const;
};