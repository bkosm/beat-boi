#include "pch.h"

GameSounds::GameSounds(const sf::SoundBuffer& hit, const float hitVolume, const sf::SoundBuffer& miss, const float missVolume)
{
	hitSound_.setBuffer(hit);
	hitSound_.setVolume(hitVolume);
	missSound_.setBuffer(miss);
	missSound_.setVolume(missVolume);
}

void GameSounds::playMissSound()
{
	if (playMiss_)
	{
		missSound_.play();
		playMiss_ = false;
	}
}

void GameSounds::unblockMissSound()
{
	playMiss_ = true;
}

void GameSounds::playHitSound()
{
	hitSound_.play();
}

