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

	// Change blocks
	void addBlock(const Block& b);
	void addBlocks(const std::vector<Block>& blist);
	Block removeBlock(int id);

	// Get
	quadtree::Box<float> getBoundingBox() const;

	// Other
	void reloadTextures();
	void draw(RenderWindow& w) const;
	bool collides(Vector2f pos, Vector2f size) const; // assumes square
};

