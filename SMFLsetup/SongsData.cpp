#include "pch.h"

bool SongsData::loadSong(const std::string& songName)
{
	readOffset_();
	if (!songContainer_[songName].loaded)
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
					songContainer_[songName].chart.firstRow.push_back(false);
				else
					songContainer_[songName].chart.firstRow.push_back(true);
				if (readLine[1] == '0')
					songContainer_[songName].chart.secondRow.push_back(false);
				else
					songContainer_[songName].chart.secondRow.push_back(true);
				if (readLine[2] == '0')
					songContainer_[songName].chart.thirdRow.push_back(false);
				else
					songContainer_[songName].chart.thirdRow.push_back(true);
				if (readLine[3] == '0')
					songContainer_[songName].chart.fourthRow.push_back(false);
				else
					songContainer_[songName].chart.fourthRow.push_back(true);
			}

			input.close();
		}
		else
		{
			return false;
		}

		readBpm *= offset_;

		songContainer_[songName].music.openFromFile("./data/songs/" + songName + "/music.wav");
		songContainer_[songName].hitSound.loadFromFile("./data/songs/" + songName + "/hitsound.wav");
		songContainer_[songName].missSound.loadFromFile("./data/songs/" + songName + "/misssound.wav");
		songContainer_[songName].bpm = readBpm;
		songContainer_[songName].beatDuration = 60.0f / readBpm;
		songContainer_[songName].loaded = true;
	}
	return true;
}

void SongsData::unloadSongs()
{
	songContainer_.clear();
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

Song& SongsData::getSong(const std::string & songName)
{
	return songContainer_[songName];
}
