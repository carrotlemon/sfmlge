#include "Menu.h"

#include <SFML/Graphics.hpp>
#include "Button.h"

// Constructor for empty menu (no menu open)
Menu::Menu() :
    name(""), pos(Vector2f(0, 0)), size(Vector2f(0, 0)) {
    boundary = { 0, 0 ,0, 0 };
    buttons = new quadtree::QuadTree<Button,
        std::function<quadtree::Box<float>(const Button&)>,
        std::function<bool(const Button&, const Button&)>>(
        boundary,
        [](const Button& b) {return b.getBoundingBox(); },
        [](const Button& a, const Button& b) {return a.equals(b); }
    );
}

Menu::Menu(std::string& n, Vector2f p, Vector2f s) : 
        name(n), pos(p), size(s) {
    boundary = {p.x, p.y, s.x, s.y};
    buttons = new quadtree::QuadTree<Button,
        std::function<quadtree::Box<float>(const Button&)>,
        std::function<bool(const Button&, const Button&)>>(
        boundary,
        [](const Button& b) {return b.getBoundingBox(); },
        [](const Button& a, const Button& b) {return a.equals(b); }
    );
}

void Menu::click(Vector2f mousePos) {

}


