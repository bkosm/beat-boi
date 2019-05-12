#include "pch.h"
#include "SongsData.hpp"
#include <fstream>

void SongsData::loadSong(const std::string& songName)
{
	if (!this->songContainer_[songName].loaded)
	{
		int readBpm{};
		std::ifstream input("./data/" + songName + "/data.bin");
		if (input.is_open())
		{
			input >> readBpm;
			std::string readLine;

			while (!input.eof())
			{
				input >> readLine;

				if (readLine[0] == '0')
					this->songContainer_[songName].chart.firstRow.push_back(false);
				else
					this->songContainer_[songName].chart.firstRow.push_back(true);
				if (readLine[1] == '0')
					this->songContainer_[songName].chart.secondRow.push_back(false);
				else
					this->songContainer_[songName].chart.secondRow.push_back(true);
				if (readLine[2] == '0')
					this->songContainer_[songName].chart.thirdRow.push_back(false);
				else
					this->songContainer_[songName].chart.thirdRow.push_back(true);
				if (readLine[3] == '0')
					this->songContainer_[songName].chart.fourthRow.push_back(false);
				else
					this->songContainer_[songName].chart.fourthRow.push_back(true);
			}

			input.close();
		}

		this->songContainer_[songName].music.openFromFile("./data/" + songName + "/music.wav");
		this->songContainer_[songName].bpm = readBpm;
		this->songContainer_[songName].beatDuration = 60.0f / readBpm;
		this->songContainer_[songName].loaded = true;
	}
}

void SongsData::unloadSongs()
{
	this->songContainer_.clear();
}

Song& SongsData::getSong(const std::string & songName)
{
	return this->songContainer_[songName];
}
