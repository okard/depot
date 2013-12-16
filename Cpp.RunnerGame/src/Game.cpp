
#include "Game.hpp"

#include <iostream>


Game::Game()
	: window_(sf::VideoMode(800, 600), "Runner")
{
	//configuration
	window_.setFramerateLimit(60);

	//setup player and level
	player_.setPosition(0, 0);
	level_.size() = sf::Vector2f(window_.getSize().x, window_.getSize().y);

	//setup camera
	camera_ = window_.getView();
	camera_.move(0, -((float)window_.getSize().y));
	camera_.zoom(1.2f);
	window_.setView(camera_);
}

Game::~Game()
{

}

void Game::startGame()
{
	state_ = GameState::Running;
	player_.setPosition(0, 0);
	level_.restart();
}

void Game::run()
{
	while (window_.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window_.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window_.close();

			//handle events
			handleEvents(event);
		}

		unsigned int timeElapsed = timer_.restart().asMilliseconds();

		// clear the window with black color
		window_.clear(sf::Color::Black);


		if(state_ == GameState::Running)
		{
			player_.update(timeElapsed);
			level_.update(timeElapsed);

			if(level_.hit(player_.getBoundingBox()))
			{
				std::cout << "hit: " << level_.way_length() << std::endl;
				state_ = GameState::Pause;
				//game over
			}
		}

		player_.draw(window_);
		level_.draw(window_);

		// end the current frame
		window_.display();
	}
}


void Game::handleEvents(const sf::Event& event)
{
	switch(event.type)
	{
	//keyboard
	case sf::Event::KeyPressed:
		switch(event.key.code)
		{
		case sf::Keyboard::Escape:
			window_.close();
			break;

		case sf::Keyboard::Return:
			startGame();
			break;

		case sf::Keyboard::Space:
			player_.jump();
			break;

		case sf::Keyboard::C:
			player_.crouch();
			break;

		default: break;
		}
		break;

	default: break;
	}
}


void Game::draw()
{

}
