#include "Room.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

#include "Block.h"
#include "Box.h"
#include "QuadTree.h"


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

// Change blocks ----------------------------------------------------------------
void Room::addBlock(const Block& b) {
	if (blocks->query(b.getBoundingBox()).size() == 0)
		blocks->add(b);
}

void Room::addBlocks(const std::vector<Block>& blist) {
	for (Block b : blist) {
		addBlock(b);
	}
}

Block Room::removeBlock(int id) {
	Block temp = Block(Vector2f(0, 0), Vector2f(1, 1), id);
	blocks->remove(temp);
	return temp;
}

// Get ----------------------------------------------------------------
quadtree::Box<float> Room::getBoundingBox() const {
	return boundary;
}

// Other ----------------------------------------------------------------
void Room::reloadTextures() {
	std::vector<Block> blist = blocks->getAllValues();
	for (Block b : blist) {
		b.reloadTexture();
	}
}

void Room::draw(RenderWindow& w) const {
	std::vector<Block> blist = blocks->query(boundary);
	for (Block b : blist) {
		b.draw(w);
	}
}

bool Room::collides(Vector2f pos, Vector2f size) const {
	if(!boundary.contains(quadtree::Box<float>(pos, size)))
		return true;

	std::vector<Block> blist = blocks->query(quadtree::Box<float>(pos.x, pos.y, size.x, size.y));
	if (blist.size() > 0) {
		for (Block b : blist) {
			if(b.isHitBoxToggled())
				return true;
		}
	}
		
	return false;
}