#pragma once

struct Particle
{
	sf::Vector2f velocity;
	sf::Time lifetime;
};

class HitParticles : public sf::Drawable, public sf::Transformable
{
public:
	HitParticles(unsigned count);

	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);

private:
	std::vector<Particle> particles_;
	sf::VertexArray vertices_;
	sf::Time lifetime_;
	sf::Vector2f emitter_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void resetParticle_(std::size_t index);
};

struct EffectParticles
{
	sf::Clock clock;
	HitParticles one, two, three, four;
	bool drawOne{ true }, drawTwo{ true }, drawThree{ true }, drawFour{ true };

	EffectParticles();

	void updateAll();
	void dontDraw();
	void draw(sf::RenderWindow& window) const;
};