#pragma once

struct SongChart
{
	std::vector<bool> firstRow, secondRow, thirdRow, fourthRow;
};

struct Song
{
	SongChart chart;
	sf::Music music;
	int bpm{};
	float beatDuration{};
	bool loaded = false;
};

class SongsData
{
public:
	SongsData() = default;
	~SongsData() = default;

	void unloadSongs();
	void loadSong(const std::string& songName);
	Song& getSong(const std::string& songName);

private:
	std::map<std::string, Song> songContainer_;
};

