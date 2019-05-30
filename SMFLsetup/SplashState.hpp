#pragma once

class SplashState : public State
{
public:
	SplashState(std::shared_ptr<GameData> data);

	void handleInput() override;
	void update() override;
	void draw() override;

private:
	std::shared_ptr<GameData> data_;

	sf::Sprite bg_;
};
