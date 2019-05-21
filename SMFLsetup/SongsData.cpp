#include "pch.h"

bool SongsData::loadSong(const std::string& songName)
{
	if (!songContainer_[songName].loaded)
	{
		float readBpm{};
		std::ifstream input("./data/" + songName + "/data.bin");
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

		songContainer_[songName].music.openFromFile("./data/" + songName + "/music.wav");
		songContainer_[songName].sfx.kick.loadFromFile("./data/" + songName + "/kick.wav");
		songContainer_[songName].sfx.clap.loadFromFile("./data/" + songName + "/clap.wav");
		songContainer_[songName].sfx.hat.loadFromFile("./data/" + songName + "/hat.wav");
		songContainer_[songName].sfx.perc.loadFromFile("./data/" + songName + "/perc.wav");
		songContainer_[songName].bpm = readBpm;
		songContainer_[songName].beatDuration = 60.0f / readBpm;
		songContainer_[songName].loaded = true;

		songContainer_[songName].bpm *= TEMPO_CORRECTION;
	}
	return true;
}

void SongsData::unloadSongs()
{
	songContainer_.clear();
}

Song& SongsData::getSong(const std::string & songName)
{
	return songContainer_[songName];
}
