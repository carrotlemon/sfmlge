#include "Block.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>

using namespace sf;

Block::Block(Vector2f p, Vector2f s) {
	pos = p;
	size = s;
}

Block::Block(Vector2f p, Vector2f s, const std::string& str) {
	pos = p;
	size = s;
	if (!texture.loadFromFile(str)) {
		std::cout << "Error Loading Image: " << str << std::endl;
	}
	sprite.setTexture(texture);
}

bool Block::collides(Vector2f p, Vector2f s) { // Assumes both are Rectangles
	// AABB - Axis Aligned Bounding Box
	//std::cout << pos.x << " " << pos.y << " " << p.x << " " << p.y << " " << size.x << " " << size.y << " " << s.x << " " << s.y << std::endl;
	//std::cout << "running collides" << std::endl;
	bool result = (
		pos.x < p.x + s.x &&
		pos.x + size.x > p.x &&
		pos.y < p.y + s.y &&
		pos.y + size.y > p.y
		);
	if (result) {
		std::cout << result << std::endl;
	}
	return (
			pos.x < p.x + s.x &&
			pos.x + size.x > p.x &&
			pos.y < p.y + s.y &&
			pos.y + size.y > p.y
		);


}

void Block::draw(RenderWindow& w) {
	sprite.setPosition(pos);
	w.draw(sprite);
}

Vector2f Block::getPos() {
	return pos;
}

Vector2f Block::getSize() {
	return size;
}

std::ostream& operator<< (std::ostream& os, const Block& v)
{
	return os << "Block: Position: " << v.pos.x << " " << v.pos.y << " Size: " << v.size.x << " " << v.size.y;
}
