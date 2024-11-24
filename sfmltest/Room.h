#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>
#include "Block.h"
#include "Box.h"
#include "QuadTree.h"


using namespace sf;

class Room
{
private:
	std::string name;
	quadtree::Box<float> boundary;
	quadtree::QuadTree<Block,
		std::function<quadtree::Box<float>(const Block&)>,
		std::function<bool(const Block&, const Block&)>> *blocks;
	Vector2f pos;
	Vector2f size;
public:
	Room();
	Room(const std::string& n, Vector2f p, Vector2f s);
	void addBlock(const Block& b);
	Block removeBlock(int id);
	void draw(RenderWindow& w);
	bool collides(Vector2f pos, Vector2f size); // assumes square
};

