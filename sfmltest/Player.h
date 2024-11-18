#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;

class Player
{
private:
	Texture texture;
	Sprite sprite;
	Vector2f pos;
	Vector2f size;
public:
	Player(const std::string& str);
	void draw(RenderWindow& w);
	void setPos(Vector2f);
	void move(Vector2f);
	void setSize(Vector2f);
	Vector2f getPos();
	Vector2f getSize();

	friend std::ostream& operator<< (std::ostream& os, const Player& v);
};

