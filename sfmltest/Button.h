#pragma once

#include <iostream>
#include <functional>
#include "Box.h"
#include "QuadTree.h"
#include <vector>

using namespace sf;

class Button
{
private:
    std::string id;
    Texture texture;
    Sprite sprite;
    bool& toggle;
    Vector2f pos;
    Vector2f size;
	std::function<void()> action;
public:
  Button(const std::string& identity, const std::string& str, Vector2f p, Vector2f s, bool& b, std::function<void()> a);
  Button(const Button& other);
  void setAction(std::function<void()> func);
  bool click();
  quadtree::Box<float> getBoundingBox() const;
  bool equals(const Button& other) const;
  void draw(RenderWindow& w);

  friend std::ostream& operator<< (std::ostream& os, const Button& v);
};

