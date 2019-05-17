#include "pch.h"
#include "Collision.hpp"

bool Collision::scoreCollision(const sf::Sprite& first, const sf::Sprite& second)
{
	if (second.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y - first.getGlobalBounds().height))
	{
		return true;
	}

	return false;
}
