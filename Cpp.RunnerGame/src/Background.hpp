
#pragma once
#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

/**
* Three Layer Parallax Scrolling
*/
class Background 
{
private:

	sf::Texture texSky_;
	sf::Texture texBackground_;
	sf::Texture texForeground_;
	
	sf::Sprite sprSky_;
	sf::Sprite sprBackground_;
	sf::Sprite sprForeground_;
	
	float speedSky_ = 0.1f;
	float speedBackground_ = 0.3f;

public:
	Background();
	
	void update(unsigned int elapsedTimeMS);
	void draw(sf::RenderTarget& target);
	
};


#endif 
