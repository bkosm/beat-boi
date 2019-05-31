#include "pch.h"
#include <regex>

EndGameState::EndGameState(std::shared_ptr<GameData> data, std::string songName, const int score, const int combo) :
	data_(std::move(data)),
	songName_(std::move(songName)),
	score_(score),
	combo_(combo)
{
	data_->applauseSound.play();

	processBestScore_();

	bg_.setTexture(data_->assets.getTexture("end bg"));

	scoreText_.setFont(data_->assets.getFont("MAIN"));
	scoreText_.setString(std::to_string(score_));
	scoreText_.setCharacterSize(25);
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setOrigin(scoreText_.getGlobalBounds().width, 0);
	scoreText_.setPosition(float(WIN_RES.x * 0.95), float(WIN_RES.y * 0.14));

	comboText_.setFont(data_->assets.getFont("MAIN"));
	comboText_.setString(std::to_string(combo_));
	comboText_.setCharacterSize(25);
	comboText_.setFillColor(sf::Color::White);
	comboText_.setOrigin(comboText_.getGlobalBounds().width, 0);
	comboText_.setPosition(float(WIN_RES.x * 0.95), float(WIN_RES.y * 0.23));

	bestScoreText_.setFont(data_->assets.getFont("MAIN"));
	bestScoreText_.setString(bestScore_);
	bestScoreText_.setCharacterSize(25);
	bestScoreText_.setFillColor(sf::Color::White);
	bestScoreText_.setOrigin(bestScoreText_.getGlobalBounds().width, 0);
	bestScoreText_.setPosition(float(WIN_RES.x * 0.7), float(WIN_RES.y * 0.435));

	bestComboText_.setFont(data_->assets.getFont("MAIN"));
	bestComboText_.setString(bestCombo_);
	bestComboText_.setCharacterSize(25);
	bestComboText_.setFillColor(sf::Color::White);
	bestComboText_.setOrigin(bestComboText_.getGlobalBounds().width, 0);
	bestComboText_.setPosition(float(WIN_RES.x * 0.7), float(WIN_RES.y * 0.523));

	restart_.setSize(sf::Vector2f(400, 40));
	restart_.setFillColor(sf::Color::Transparent);
	restart_.setPosition(float(WIN_RES.x * 0.01), float(WIN_RES.y * 0.7));

	exit_.setSize(sf::Vector2f(400, 40));
	exit_.setFillColor(sf::Color::Transparent);
	exit_.setPosition(float(WIN_RES.x * 0.01), float(WIN_RES.y * 0.8));
}

void EndGameState::handleInput()
{
	sf::Event event{};

	while (data_->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			data_->window.close();
		}
	}

	if (InputManager::isShapeClicked(restart_, sf::Mouse::Left, data_->window) && !clicked_ || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !clicked_)
	{
		clicked_ = true;
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<OptionsState>(data_, songName_), true);
	}
	if (InputManager::isShapeClicked(exit_, sf::Mouse::Left, data_->window) && !clicked_ || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !clicked_)
	{
		clicked_ = true;
		data_->transitionSound.play();
		data_->maschine.addState(std::make_unique<MainMenuState>(data_), true);
	}
}

void EndGameState::update() {}

void EndGameState::draw()
{
	data_->window.clear();
	data_->window.draw(bg_);
	data_->window.draw(restart_);
	data_->window.draw(exit_);
	data_->window.draw(scoreText_);
	data_->window.draw(comboText_);
	data_->window.draw(bestScoreText_);
	data_->window.draw(bestComboText_);
	data_->window.display();
}

void EndGameState::processBestScore_()
{
	if (!processed_)
	{
		processed_ = true;
		std::ifstream input("./data/scores.bb");
		if (input.is_open())
		{
			std::string file;
			while (!input.eof())
			{
				std::string toAppend;
				input >> toAppend;
				file += toAppend + '\n';
			}
			input.close();
			std::regex ex(songName_ + R"(\s(\d*)\s(\d*))");
			std::smatch match;
			if (std::regex_search(file, match, ex))
			{
				if (std::stoi(match.str(1)) > score_) //Old highscore
				{
					bestScore_ = match.str(1);
					bestCombo_ = match.str(2);
				}
				else //Overwrite highscore
				{
					bestScore_ = "NEW";
					bestCombo_ = "BEST!";
					input.open("./data/scores.bb");
					std::ofstream rewrite("./data/scoresTemp.bb");
					if (input.is_open() && rewrite.is_open())
					{
						std::string toReplace = match.str(1), replacing = std::to_string(score_), temp;
						while (input >> temp)
						{
							if (temp == toReplace)
							{
								temp = replacing;
								toReplace = match.str(2);
								replacing = std::to_string(combo_);
							}
							rewrite << temp + '\n';
						}
						input.close();
						rewrite.close();
						std::remove("./data/scores.bb");
						std::rename("./data/scoresTemp.bb", "./data/scores.bb");
					}
				}
			}
			else //New highscore
			{
				bestScore_ = "NEW";
				bestCombo_ = "BEST!";
				std::ofstream output("./data/scores.bb", std::ios::app);
				if (output.is_open())
				{
					output << songName_ + '\n' + std::to_string(score_) + '\n' + std::to_string(combo_) + '\n';
				}
				output.close();
			}
		}
		else //Error reading file
		{
			bestScore_ = "scores file";
			bestCombo_ = "missing!";

			std::ofstream out("./data/scores.bb");
			if (out.is_open())
			{
				out << "";
			}
			out.close();
		}
	}
}