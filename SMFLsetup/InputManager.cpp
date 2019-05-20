#include "pch.h"

bool InputManager::isSpriteClicked(const sf::Sprite& object, const sf::Mouse::Button& button,
	const sf::RenderWindow& window) const
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(int(object.getPosition().x), int(object.getPosition().y), int(object.getGlobalBounds().width),
			int(object.getGlobalBounds().height));

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::isTextClicked(const sf::Text& object, const sf::Mouse::Button& button,
	const sf::RenderWindow& window) const
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(int(object.getPosition().x), int(object.getPosition().y), int(object.getGlobalBounds().width),
			int(object.getGlobalBounds().height));

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

sf::Vector2i InputManager::getMousePosition(const sf::RenderWindow& window) const
{
	return sf::Mouse::getPosition(window);
}

bool InputManager::scoreCollision(const sf::Sprite& first, const sf::Sprite& second)
{
	if (second.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y - first.getGlobalBounds().height))
	{
		return true;
	}

	return false;
}