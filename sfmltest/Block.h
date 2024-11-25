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
	Block(Vector2f p, Vector2f s, int i, bool b = true);
	Block(Vector2f p, Vector2f s, const std::string& str, bool b = true);
	Block(const Block& other);

	Vector2f getPos();
	Vector2f getSize();
	bool isHitBoxToggled();
	bool collides(Vector2f p, Vector2f s);

	void setHitBoxToggle(bool b);

	void reloadTexture();
	void draw(RenderWindow& w);
	bool equals(const Block& other) const;
	
	quadtree::Box<float> getBoundingBox() const;

	friend std::ostream& operator<< (std::ostream& os, const Block& v);
};

