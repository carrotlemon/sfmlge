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
	// Constructors
	Room();
	Room(const std::string& n, Vector2f p, Vector2f s);

	// Map Builder Tools
	void fill(Vector2f pos, Vector2f blockSize, Vector2f fillSize, int id, bool hitboxtoggle = true);
	void outline(Vector2f pos, Vector2f blockSize, Vector2f fillSize, int id, bool hitboxtoggle = true);

	// Change blocks
	void addBlock(const Block& b);
	Block removeBlock(int id);

	// Other
	void draw(RenderWindow& w);
	bool collides(Vector2f pos, Vector2f size); // assumes square
};

