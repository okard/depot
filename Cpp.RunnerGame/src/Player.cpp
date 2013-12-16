
#include "Player.hpp"

#include <iostream>
//(sf::Vector2f(120, 50))


Player::Player()
	: sprite_(sf::Vector2f(50, 120))
{
	sprite_.setFillColor(sf::Color::Green);
}

Player::~Player()
{
}

void Player::setPosition(float x, float y)
{
	sprite_.setPosition(x,y-sprite_.getSize().y);
}

sf::FloatRect Player::getBoundingBox()
{
	return sprite_.getGlobalBounds();
}

void Player::jump()
{
	if(!moving_ && !crouching_)
	{
		moving_ = true;
		acceleration_ = 0.8f;
	}
}

void Player::crouch()
{
	if(!moving_ && !crouching_)
	{
		crouching_ = true;
		const float height = sprite_.getSize().y/2;
		sprite_.setSize(sf::Vector2f(sprite_.getSize().x, height));
		sprite_.move(0.f, height);

		acceleration_ = 1.5f;
	}
}

void Player::update(unsigned int elapsedTimeMS)
{
	//16 ms for 60fps
	//std::cout << elapsedTimeMS << std::endl;
	//const float posy = sprite_.getPosition().y - sprite_.getSize().y;
	if(moving_)
	{
		float moveY = -(elapsedTimeMS * acceleration_);
		sprite_.move(0.f, moveY);
		acceleration_ -= gravity_;

		if(sprite_.getPosition().y > -sprite_.getSize().y)
		{
			sprite_.setPosition(sprite_.getPosition().x, -sprite_.getSize().y);
			moving_ = false;
		}
	}

	if(crouching_)
	{
		acceleration_ -= gravity_;

		if(acceleration_ < 0.f)
		{
			sprite_.setSize(sf::Vector2f(sprite_.getSize().x, sprite_.getSize().y*2.f));
			setPosition(0.f, 0.f);
			crouching_ = false;
		}
	}
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(sprite_);
}
