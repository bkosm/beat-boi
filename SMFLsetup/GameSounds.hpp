#pragma once
class GameSounds
{
public:
	GameSounds(const sf::SoundBuffer& hit, float hitVolume, const sf::SoundBuffer& miss, float missVolume);
	~GameSounds() = default;

	void playMissSound();
	void unblockMissSound();
	void playHitSound();

private:
	sf::Sound hitSound_, missSound_;

	bool playMiss_{ true };
};

