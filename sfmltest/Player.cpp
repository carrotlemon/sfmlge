#include "Player.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Room.h"
#include "Block.h"

using namespace sf;

// Constructors ----------------------------------------------------------------
Player::Player(const std::string& str) {
	if (!texture.loadFromFile(str)) {

	}
	sprite.setTexture(texture);
	size = Vector2f(64.f, 64.f);
}

// Set ----------------------------------------------------------------
void Player::move(Vector2f m) {
	pos.x += m.x;
	pos.y += m.y;
}

void Player::setPos(Vector2f p) {
	pos = p;
}

void Player::setSize(Vector2f s) {
	size = s;
}

// Get ----------------------------------------------------------------
Vector2f Player::getPos() {
	return pos;
}

Vector2f Player::getSize() {
	return size;
}

// Other ----------------------------------------------------------------
void Player::draw(RenderWindow& w) {
	sprite.setPosition(pos);
	w.draw(sprite);
}

std::ostream& operator<< (std::ostream& os, const Player& v) {
	return os << "Player: Position: " << v.pos.x << " " << v.pos.y << " Size: " << v.size.x << " " << v.size.y;
}