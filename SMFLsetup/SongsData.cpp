#include "pch.h"

bool SongsData::loadSong(const std::string& songName)
{
	readOffset_();
	if (!song_.loaded)
	{
		float readBpm{};
		std::ifstream input("./data/songs/" + songName + "/data.bin");
		if (input.is_open())
		{
			input >> readBpm;
			std::string readLine;

			while (!input.eof())
			{
				input >> readLine;

				if (readLine[0] == '0')
					song_.chart.firstRow.push_back(false);
				else
					song_.chart.firstRow.push_back(true);
				if (readLine[1] == '0')
					song_.chart.secondRow.push_back(false);
				else
					song_.chart.secondRow.push_back(true);
				if (readLine[2] == '0')
					song_.chart.thirdRow.push_back(false);
				else
					song_.chart.thirdRow.push_back(true);
				if (readLine[3] == '0')
					song_.chart.fourthRow.push_back(false);
				else
					song_.chart.fourthRow.push_back(true);
			}

			input.close();
		}
		else
		{
			return false;
		}

		readBpm *= offset_;

		song_.music.openFromFile("./data/songs/" + songName + "/music.wav");
		song_.hitSound.loadFromFile("./data/songs/" + songName + "/hitsound.wav");
		song_.missSound.loadFromFile("./data/songs/" + songName + "/misssound.wav");
		song_.bpm = readBpm;
		song_.beatDuration = 60.0f / readBpm;
		song_.loaded = true;
	}
	return true;
}

void SongsData::unloadSong()
{
	song_.loaded = false;
	song_.chart.firstRow.clear();
	song_.chart.secondRow.clear();
	song_.chart.thirdRow.clear();
	song_.chart.fourthRow.clear();
}

void SongsData::readOffset_()
{
	std::ifstream input("./data/offset.bb");
	if (input.is_open())
	{
		input >> offset_;
	}
	else
	{
		offset_ = 1.001f;
	}
	input.close();
}

Song& SongsData::getSong()
{
	return song_;
}
