
#include "Level.hpp"

#include <iostream>

Level::Level()
{
	//plant 
	if (!texPlant_.loadFromFile("data/plant.png"))
	{
		std::cerr << "Can't load texture plant.png" << std::endl;
		throw;
	}
	
	//stone 
	if (!texStone_.loadFromFile("data/stone.png"))
	{
		std::cerr << "Can't load texture plant.png" << std::endl;
		throw;
	}
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

	//loop through blocks and check for hitting
	//todo optimize check only front block?
	for(auto& b: blocks_)
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


	//update position of all available blocks
	for(unsigned int i=0; i < blocks_.size(); i++)
	{
		blocks_[i].move(-movement, 0.f);
	}

	//add new blocks each 500 distance
	if( lastBlockX_ > 500.f)
	{
		std::uniform_int_distribution<int> height_gen(20,80);
		std::uniform_int_distribution<int> width_gen(50,80);

		//make decision a floating stone or a bottom plant
		

		std::uniform_int_distribution<int> ypos_gen(0, 130);

		//add over time gone higher change to add a block to posx_ end
		sf::Sprite b(texStone_);
		auto texSize = texStone_.getSize();
		b.setScale((float)width_gen(gen_) / (float)texSize.x , (float)height_gen(gen_) / (float)texSize.y);
		
		
		b.setPosition(size_.x,  - ypos_gen(gen_) - baseHeight_);
		blocks_.push_back(b);

		lastBlockX_ = 0.f;
	}

	//remove blocks when gone
	if(blocks_.front().getPosition().x < 0.f)
		blocks_.pop_front();

	//blocks left posx_ remove from que
}

void Level::draw(sf::RenderTarget& target)
{
	//draw blocks
	for(auto& b: blocks_)
	{
		target.draw(b);
	}
}
