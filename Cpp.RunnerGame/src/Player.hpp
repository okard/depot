#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

/**
* Spieler
*/
class Player
{
private:
	sf::RectangleShape sprite_;

	//speed
	bool moving_ = false;
	bool crouching_ = false;
	float speed_ = 0.f; //relative speed
	float acceleration_ = 0.f;
	const float gravity_ = 0.03f;

public:

	Player();
	~Player();

	void jump();
	void crouch();

	void setPosition(float x, float y);

	sf::FloatRect getBoundingBox();

	void update(unsigned int elapsedTimeMS);
	void draw(sf::RenderTarget& target);

};

#endif
