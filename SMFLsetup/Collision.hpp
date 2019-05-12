#pragma once

class Collision
{
public:
	Collision() = default;
	~Collision() = default;

	static bool scoreCollision(const sf::Sprite& first, const sf::Sprite& second);
};

