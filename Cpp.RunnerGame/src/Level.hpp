
#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <deque>
#include <random>

#include <SFML/Graphics.hpp>


class Level
{
private:

	//complete level size from 0,0 to size_
	sf::Vector2f size_;

	//position in level starting at 0,0
	float posx_ = 0.f;
	float lastBlockX_ = 0.f;

	//speed
	float speed_ = 0.5f;

	// actual drawings block
	std::deque<sf::RectangleShape> blocks_;

	//grad

	//wahrscheinlichkeit basierend auf zeit gone

	std::mt19937 gen_;

public:
	Level();
	~Level();

	bool hit(const sf::FloatRect& boundingBox);

	void restart();

	void update(unsigned int elapsedTimeMS);
	void draw(sf::RenderTarget& target);

	inline float way_length() { return posx_; }

	inline sf::Vector2f& size(){return size_;}
};


#endif
