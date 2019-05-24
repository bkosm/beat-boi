#pragma once

class SplashState : public State
{
public:
	SplashState(GameDataRef data);

	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;

private:
	GameDataRef data_;

	sf::Sprite bg_;
};
