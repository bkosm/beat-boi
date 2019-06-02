#pragma once

struct SongChart
{
	std::vector<bool> firstRow, secondRow, thirdRow, fourthRow;
};

struct Song
{
	SongChart chart;
	sf::Music music;
	sf::SoundBuffer hitSound, missSound;
	float bpm{}, beatDuration{};
	bool loaded = false;
};

class SongsData
{
public:
	SongsData() = default;
	~SongsData() = default;

	void unloadSong();
	bool loadSong(const std::string& songName);
	Song& getSong();

private:
	Song song_;
	float offset_{};

	void readOffset_();
};

