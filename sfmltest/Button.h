#pragma once

#include <iostream>
#include <functional>
#include "Box.h"
#include "QuadTree.h"

using namespace sf;

class Button
{
private:
    std::string id;
    Texture texture;
    Sprite sprite;
	std::function<void()> action;
    Vector2f pos;
    Vector2f size;
public:
    Button();
    Button(const std::string& identity);
    Button(const std::string& identity, const std::string& str, Vector2f p, Vector2f s, std::function<void()> a);
    void setAction(std::function<void()> func);
    void click();
    quadtree::Box<float> getBoundingBox() const;
    bool equals(const Button& other) const;
    void draw(RenderWindow& w);
};

