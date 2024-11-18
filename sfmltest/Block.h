#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>

using namespace sf;

class Block
{
private:
	Texture texture;
	Sprite sprite;
	Vector2f pos;
	Vector2f size;
public:
	Block(Vector2f p, Vector2f s);
	Block(Vector2f p, Vector2f s, const std::string& str);
	bool collides(Vector2f p, Vector2f s);
	void draw(RenderWindow& w);
	Vector2f getPos();
	Vector2f getSize();

	friend std::ostream& operator<< (std::ostream& os, const Block& v);
};

