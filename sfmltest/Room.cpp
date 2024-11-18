#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Room.h"
#include "Block.h"

using namespace sf;

Room::Room(std::vector<Block> bs) {
	blocks = bs;
}
Room::Room() {

}

void Room::draw(RenderWindow& w) {
	w.draw(RectangleShape(Vector2f(100.f, 100.f)));
	for (Block b : blocks) {
		b.draw(w);
	}
}

bool Room::collides(Vector2f pos, Vector2f size) {
	for (Block b : blocks) {
		if (b.collides(pos, size))
			return true;
	}
	return false;
}