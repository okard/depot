
#include "Level.hpp"


Level::Level()
{
}

Level::~Level()
{
}


void Level::restart()
{
	posx_ = 0.f;
	lastBlockX_ = 0.f;
	blocks_.clear();
}

bool Level::hit(const sf::FloatRect& boundingBox)
{

	//draw blocks
	for(auto b: blocks_)
	{
		if(b.getGlobalBounds().intersects(boundingBox))
			return true;
	}

	return false;
}

void Level::update(unsigned int elapsedTimeMS)
{
	const float movement = speed_ * elapsedTimeMS;
	posx_ += movement;
	lastBlockX_ += movement;


	//update available blocks
	for(unsigned int i=0; i < blocks_.size(); i++)
	{
		blocks_[i].move(-movement, 0.f);
	}

	//add new blocks
	if( lastBlockX_ > 500.f)
	{
		std::uniform_int_distribution<int> height_gen(20,80);
		std::uniform_int_distribution<int> width_gen(50,80);

		std::uniform_int_distribution<int> ypos_gen(0, 130);

		//add over time gone higher change to add a block to posx_ end
		sf::RectangleShape b(sf::Vector2f(width_gen(gen_), height_gen(gen_)));
		b.setPosition(size_.x-b.getSize().x, -b.getSize().y - ypos_gen(gen_));
		blocks_.push_back(b);

		lastBlockX_ = 0.f;
	}

	//remove blocks when gone
	if(blocks_.front().getPosition().x + blocks_.front().getSize().x < 0.f)
		blocks_.pop_front();



	//blocks left posx_ remove from que
}

void Level::draw(sf::RenderTarget& target)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(size_.x, 0))
	};

	target.draw(line, 2, sf::Lines);

	//draw blocks
	for(auto b: blocks_)
	{
		target.draw(b);
	}
}
