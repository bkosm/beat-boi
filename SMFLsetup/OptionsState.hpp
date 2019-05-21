#pragma once

class OptionsState : public State
{
public:
	OptionsState(GameDataRef data, std::string songName);

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Text optionsText_, returnText_, playText_, infoText_;

	std::string songName_;
};
