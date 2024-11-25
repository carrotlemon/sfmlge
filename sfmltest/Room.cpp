#include "Room.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Block.h"
#include "Box.h"
#include "QuadTree.h"
#include <functional>

using namespace sf;

// Constructors ----------------------------------------------------------------
Room::Room() {

}

Room::Room(const std::string& n, Vector2f p, Vector2f s) : 
	name(n), pos(p), size(s) {
	boundary = { p.x, p.y, s.x, s.y };
	blocks = new quadtree::QuadTree<Block,
		std::function<quadtree::Box<float>(const Block&)>,
		std::function<bool(const Block&, const Block&)>>(
			boundary,
			[](const Block& b) {return b.getBoundingBox(); },
			[](const Block& a, const Block& b) {return a.equals(b); }
			);
}

// Map Builder Tools ----------------------------------------------------------------
void Room::fill(Vector2f pos, Vector2f blockSize, Vector2f fillSize, int id, bool hitboxtoggle) {
	for (int row = 0; row <= fillSize.y; ++row) {
		for (int col = 0; col <= fillSize.x; ++col) {
			Block block(Vector2f(pos.x + blockSize.x * col, pos.y + blockSize.y * row), blockSize, id);
			if (!hitboxtoggle)
				block.setHitBoxToggle(false);
			addBlock(block);
		}
	}
}

void Room::outline(Vector2f pos, Vector2f blockSize, Vector2f fillSize, int id, bool hitboxtoggle) {
	// top and bottom
	for (int row = 0; row <= fillSize.y; row += fillSize.y) {
		for (int col = 0; col <= fillSize.x; ++col) {
			Block block(Vector2f(pos.x + blockSize.x * col, pos.y + blockSize.y * row), blockSize, id);
			if (!hitboxtoggle)
				block.setHitBoxToggle(false);
			addBlock(block);
		}
	}
	// sides
	for (int row = 1; row <= fillSize.y-1; ++row) {
		for (int col = 0; col <= fillSize.x; col += fillSize.x) {
			Block block(Vector2f(pos.x + blockSize.x * col, pos.y + blockSize.y * row), blockSize, id);
			if (!hitboxtoggle)
				block.setHitBoxToggle(false);
			addBlock(block);
		}
	}
}


// Change blocks ----------------------------------------------------------------
void Room::addBlock(const Block& b) {
	if (blocks->query(b.getBoundingBox()).size() == 0)
		blocks->add(b);
}

Block Room::removeBlock(int id) {
	Block temp = Block(Vector2f(0, 0), Vector2f(1, 1), id);
	blocks->remove(temp);
	return temp;
}

// Other ----------------------------------------------------------------
void Room::draw(RenderWindow& w) {
	std::vector<Block> blist = blocks->query(boundary);
	for (Block b : blist) {
		b.draw(w);
	}
}

bool Room::collides(Vector2f pos, Vector2f size) {
	std::vector<Block> blist = blocks->query(quadtree::Box<float>(pos.x, pos.y, size.x, size.y));
	if (blist.size() > 0) {
		for (Block b : blist) {
			if(b.isHitBoxToggled())
				return true;
		}
	}
		
	return false;
}