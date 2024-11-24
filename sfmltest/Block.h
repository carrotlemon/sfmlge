#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "Box.h"

using namespace sf;

class Block
{
private:
	int id;
	bool hitboxtoggle;
	Texture texture;
	Sprite sprite;
	Vector2f pos;
	Vector2f size;
public:
	Block(Vector2f p, Vector2f s, int i);
	Block(Vector2f p, Vector2f s, const std::string& str);
	bool collides(Vector2f p, Vector2f s);
	void draw(RenderWindow& w);
	Vector2f getPos();
	Vector2f getSize();
	void setHitBoxToggle(bool b);
	bool equals(const Block& other) const;
	bool isHitBoxToggled();
	quadtree::Box<float> getBoundingBox() const;

	friend std::ostream& operator<< (std::ostream& os, const Block& v);
};

