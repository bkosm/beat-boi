#include "pch.h"

bool InputManager::isShapeClicked(const sf::Shape& object, const sf::Mouse::Button& button,
	const sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		const sf::IntRect tempRect(int(object.getPosition().x), int(object.getPosition().y), int(object.getGlobalBounds().width),
			int(object.getGlobalBounds().height));

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::scoreCollision(const sf::Sprite& first, const sf::Sprite& second)
{
	return second.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y);
}