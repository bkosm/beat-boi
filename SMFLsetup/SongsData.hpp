#pragma once

struct SongChart
{
	std::vector<bool> firstRow, secondRow, thirdRow, fourthRow;

	void clearChart();
};

class SongsData
{
public:
	SongsData() = default;
	~SongsData() = default;

	void unloadSong();

	SongChart& getChart();
	sf::Music& getMusic();
	const sf::SoundBuffer& getHitSound() const;
	const sf::SoundBuffer& getMissSound() const;

	bool loadSong(const std::string& songName);
	unsigned chartLength() const;
	float getBeatDuration() const;
	float getBPM() const;

private:
	SongChart chart_;
	
	sf::Music music_;
	sf::SoundBuffer hitSound_, missSound_;
	
	float bpm_{}, beatDuration_{}, offset_{};
	bool loaded_ = false;

	void readOffset_();
};

