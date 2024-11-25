#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class Menu
{
private:
    std::string name;
    quadtree::Box<float> boundary;
    quadtree::QuadTree<Button,
        std::function<quadtree::Box<float>(const Button&)>,
        std::function<bool(const Button&, const Button&)>> *buttons;
    Vector2f pos;
    Vector2f size;
public:
    Menu();
    Menu(const std::string& n, Vector2f p, Vector2f s);
    void addButton(const Button& b);
    //Button removeButton(const std::string& id);
    void draw(RenderWindow& w);
    void click(Vector2i mousePos);
};

