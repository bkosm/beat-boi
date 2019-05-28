#include "pch.h"
#include <iostream>

HitParticles::HitParticles(const unsigned count) : particles_(count), vertices_(sf::Points, count), lifetime_(sf::seconds(3.f)), emitter_(0.f, 0.f)
{
}

void HitParticles::setEmitter(const sf::Vector2f position)
{
	emitter_ = position;
}

void HitParticles::update(const sf::Time elapsed)
{
	for (std::size_t i = 0; i < particles_.size(); ++i)
	{
		Particle& p = particles_[i];
		p.lifetime -= elapsed;

		if (p.lifetime <= sf::Time::Zero)
		{
			resetParticle_(i);
		}

		vertices_[i].position += p.velocity * elapsed.asSeconds();

		const float ratio = p.lifetime.asSeconds() / lifetime_.asSeconds();
		vertices_[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void HitParticles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(vertices_, states);
}

void HitParticles::resetParticle_(const std::size_t index)
{
	const auto angle = Game::randInt(0, 360) * 3.14f / 180.f;
	const auto speed = Game::randInt(50, 100);
	particles_[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	particles_[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	vertices_[index].position = emitter_;
}

EffectParticles::EffectParticles() : one(NMBR_OF_PARTICLES), two(NMBR_OF_PARTICLES), three(NMBR_OF_PARTICLES), four(NMBR_OF_PARTICLES)
{
}

void EffectParticles::updateAll()
{
	const auto elapsed = clock.restart();
	one.update(elapsed);
	two.update(elapsed);
	three.update(elapsed);
	four.update(elapsed);
}

void EffectParticles::dontDraw()
{
	drawOne = false;
	drawTwo = false;
	drawThree = false;
	drawFour = false;
}

void EffectParticles::draw(sf::RenderWindow & window) const
{
	if (drawOne)
		window.draw(one);
	if (drawTwo)
		window.draw(two);
	if (drawThree)
		window.draw(three);
	if (drawFour)
		window.draw(four);
}
