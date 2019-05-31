#pragma once

struct SongChart
{
	std::vector<bool> firstRow, secondRow, thirdRow, fourthRow;
};

struct Song
{
	SongChart chart;
	sf::Music music;
	sf::SoundBuffer hitSound;
	float bpm{}, beatDuration{};
	bool loaded = false;
};

class SongsData
{
public:
	SongsData();
	~SongsData() = default;

	void unloadSongs();
	bool loadSong(const std::string& songName);
	Song& getSong(const std::string& songName);

private:
	std::map<std::string, Song> songContainer_;
	float tempoCorrection_{};
};

