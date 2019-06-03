#include "pch.h"

bool SongsData::loadSong(const std::string& songName)
{
	readOffset_();
	if (!loaded_)
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
				{
					chart_.firstRow.push_back(false);
				}
				else
				{
					chart_.firstRow.push_back(true);
				}

				if (readLine[1] == '0')
				{
					chart_.secondRow.push_back(false);
				}
				else
				{
					chart_.secondRow.push_back(true);
				}

				if (readLine[2] == '0')
				{
					chart_.thirdRow.push_back(false);
				}
				else
				{
					chart_.thirdRow.push_back(true);
				}

				if (readLine[3] == '0')
				{
					chart_.fourthRow.push_back(false);
				}
				else
				{
					chart_.fourthRow.push_back(true);
				}
			}

			input.close();
		}
		else
		{
			return false;
		}

		readBpm *= offset_;

		music_.openFromFile("./data/songs/" + songName + "/music.wav");
		hitSound_.loadFromFile("./data/songs/" + songName + "/hitsound.wav");
		missSound_.loadFromFile("./data/songs/" + songName + "/misssound.wav");
		bpm_ = readBpm;
		beatDuration_ = 60.0f / readBpm;
		loaded_ = true;
	}
	return true;
}

unsigned SongsData::chartLength() const
{
	return chart_.firstRow.size();
}

SongChart& SongsData::getChart()
{
	return chart_;
}

sf::Music& SongsData::getMusic()
{
	return music_;
}

const sf::SoundBuffer& SongsData::getHitSound() const
{
	return hitSound_;
}

const sf::SoundBuffer& SongsData::getMissSound() const
{
	return missSound_;
}

float SongsData::getBeatDuration() const
{
	return beatDuration_;
}

float SongsData::getBPM() const
{
	return bpm_;
}

void SongChart::clearChart()
{
	firstRow.clear();
	secondRow.clear();
	thirdRow.clear();
	fourthRow.clear();
}

void SongsData::unloadSong()
{
	chart_.clearChart();
	loaded_ = false;
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