#include "pch.h"
#include "Collision.hpp"

bool Collision::scoreCollision(const sf::Sprite& first, const sf::Sprite& second)
{
	const auto secondY = second.getPosition().y;
	const auto firstY = first.getPosition().y;
	const auto secondHeight = second.getGlobalBounds().height;

	if (first.getGlobalBounds().intersects(second.getGlobalBounds()) && secondY - secondHeight / 2 < firstY && firstY < secondHeight + secondY)
	{
		return true;
	}

	return false;
}
