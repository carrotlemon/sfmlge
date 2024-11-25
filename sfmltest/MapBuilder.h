#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "QuadTree.h"
#include "Room.h"
#include "Block.h"

using namespace sf;

// Map Builder Tools ----------------------------------------------------------------
std::vector<Block> fill(Vector2f pos, Vector2f blockSize, Vector2i fillSize, int id, bool hitboxtoggle) {
	std::vector<Block> blist;
	for (int row = 0; row < fillSize.y; ++row) {
		for (int col = 0; col < fillSize.x; ++col) {
			Block block(Vector2f(pos.x + blockSize.x * col, pos.y + blockSize.y * row), blockSize, id, hitboxtoggle);
			blist.push_back(block);
		}
	}
	return blist;
}

std::vector<Block> outline(Vector2f pos, Vector2f blockSize, Vector2i fillSize, int id, bool hitboxtoggle) {
	std::vector<Block> blist;
	// top and bottom
	for (int row = 0; row <= fillSize.y; row += fillSize.y) {
		for (int col = 0; col <= fillSize.x; ++col) {
			Block block(Vector2f(pos.x + blockSize.x * col, pos.y + blockSize.y * row), blockSize, id, hitboxtoggle);
			blist.push_back(block);
		}
	}
	// sides
	for (int row = 1; row <= fillSize.y - 1; ++row) {
		for (int col = 0; col <= fillSize.x; col += fillSize.x) {
			Block block(Vector2f(pos.x + blockSize.x * col, pos.y + blockSize.y * row), blockSize, id, hitboxtoggle);
			blist.push_back(block);
		}
	}
	return blist;
}