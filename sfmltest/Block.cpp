#include "Block.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "Box.h"

using namespace sf;

// Constructors ----------------------------------------------------------------
Block::Block(Vector2f p, Vector2f s, int i) : 
	id(i), pos(p), size(s), hitboxtoggle(true) {
	std::string file = "sprites/" + std::to_string(i) + ".png";
	if (!texture.loadFromFile(file)) {
		std::cout << "Error Loading Image: " << file << std::endl;
	}
	sprite.setTexture(texture);
}

Block::Block(Vector2f p, Vector2f s, const std::string& str) : 
	id(-1), pos(p), size(s), hitboxtoggle(true) {
	if (!texture.loadFromFile(str)) {
		std::cout << "Error Loading Image: " << str << std::endl;
	}
	sprite.setTexture(texture);
}

bool Block::collides(Vector2f p, Vector2f s) { // Assumes both are Rectangles
	// AABB - Axis Aligned Bounding Box
	return hitboxtoggle && (
			pos.x < p.x + s.x &&
			pos.x + size.x > p.x &&
			pos.y < p.y + s.y &&
			pos.y + size.y > p.y
		);
}

// Action Methods ----------------------------------------------------------------
void Block::draw(RenderWindow& w) {
	sprite.setPosition(pos);
	w.draw(sprite);
}

void Block::setHitBoxToggle(bool b) {
	hitboxtoggle = b;
}

// Get methods ----------------------------------------------------------------
Vector2f Block::getPos() {
	return pos;
}

Vector2f Block::getSize() {
	return size;
}

bool Block::isHitBoxToggled() {
	return hitboxtoggle;
}

quadtree::Box<float> Block::getBoundingBox() const {
	return quadtree::Box<float>(pos.x, pos.y, size.x, size.y);
}

// Other methods ----------------------------------------------------------------
bool Block::equals(const Block& other) const {
	return id == other.id;
}

std::ostream& operator<< (std::ostream& os, const Block& v)
{
	return os << "Block: Position: " << v.pos.x << " " << v.pos.y << " Size: " << v.size.x << " " << v.size.y;
}
