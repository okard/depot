
#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Level.hpp"
#include "Background.hpp"


enum class GameState
{
	Pause,
	Running
};

/**
* The Game
*/
class Game
{
private:
	sf::RenderWindow window_;
	sf::View camera_;
	sf::Clock timer_;

	Background background_;
	Player player_;
	Level level_;

	GameState state_ = GameState::Pause;
	//status paused, running, failed

public:
	Game();
	~Game();

	void run();

	void startGame();

private:
	void handleEvents(const sf::Event& event);
	void draw();
	void update(unsigned int timeElapsedMS);

};



#endif
