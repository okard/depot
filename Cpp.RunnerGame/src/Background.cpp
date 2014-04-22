#include "Background.hpp"

#include <iostream>


static inline void moveBackground(sf::Sprite& spr, float speed, unsigned int elapsedTimeMS)
{
	auto texSize = spr.getTexture()->getSize();
	
	auto newLeft = spr.getTextureRect().left + speed * elapsedTimeMS;
	if(newLeft > texSize.x*2)
	{
		newLeft -= texSize.x;
	}
	spr.setTextureRect(sf::IntRect(newLeft, 0, texSize.x, texSize.y));
}


Background::Background()
{
	//sky texture and sprite
	if (!texSky_.loadFromFile("data/sky.png"))
	{
		std::cerr << "Can't load texture sky.png" << std::endl;
		throw;
	}
	texSky_.setRepeated(true);
	sprSky_.setTexture(texSky_);
	sprSky_.move(0.f, -static_cast<float>(texSky_.getSize().y));
	
	//background
	if (!texBackground_.loadFromFile("data/background.png"))
	{
		std::cerr << "Can't load texture background.png" << std::endl;
		throw;
	}
	texBackground_.setRepeated(true);
	sprBackground_.setTexture(texBackground_);
	sprBackground_.move(0.f, -static_cast<float>(texBackground_.getSize().y));
	
	//foreground
	if (!texForeground_.loadFromFile("data/foreground.png"))
	{
		std::cerr << "Can't load texture foreground.png" << std::endl;
		throw;
	}
	sprForeground_.setTexture(texForeground_);
	sprForeground_.move(0.f, -static_cast<float>(texForeground_.getSize().y));
}
	
void Background::update(unsigned int elapsedTimeMS)
{
	moveBackground(sprSky_, speedSky_, elapsedTimeMS);
	moveBackground(sprBackground_, speedBackground_, elapsedTimeMS);
	
}

void Background::draw(sf::RenderTarget& target)
{
	target.draw(sprSky_);
	target.draw(sprBackground_);
	target.draw(sprForeground_);
}
