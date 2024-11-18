#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Block.h"

using namespace sf;

class Room
{
private:
	std::vector<Block> blocks;
public:
	Room(std::vector<Block> bs);
	Room();
	void draw(RenderWindow& w);
	bool collides(Vector2f pos, Vector2f size); // assumes square
};

