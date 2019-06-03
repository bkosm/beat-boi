#pragma once

class Hitmarker
{
public:
	Hitmarker() = default;
	Hitmarker(const sf::Texture& texture, bool hit = false);
	~Hitmarker() = default;

	void setHit(const sf::Texture& texture);
	void setPosition(float x, float y);
	void setTexture(const sf::Texture& texture);
	void reset();

	const sf::Sprite& getSprite() const;
	sf::Sprite& getSprite();

	bool hasEmptyTex() const;
	bool isHit() const;

private:
	sf::Sprite sprite_;

	bool isHit_{};
};

