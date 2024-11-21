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
    Menu(std::string& n, Vector2f p, Vector2f s);
    void click(Vector2f mousePos);
};

