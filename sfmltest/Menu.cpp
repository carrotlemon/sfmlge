#include "Menu.h"

#include <SFML/Graphics.hpp>
#include "Button.h"

// Constructor for empty menu (no menu open)
Menu::Menu() :
    name(""), pos(Vector2f(0, 1)), size(Vector2f(1, 1)) {
    boundary = { 0, 0, 1, 1 };
    buttons = new quadtree::QuadTree<Button,
        std::function<quadtree::Box<float>(const Button&)>,
        std::function<bool(const Button&, const Button&)>>(
        boundary,
        [](const Button& b) {return b.getBoundingBox(); },
        [](const Button& a, const Button& b) {return a.equals(b); }
    );
}

Menu::Menu(const std::string& n, Vector2f p, Vector2f s) : 
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

void Menu::addButton(const Button& b) {
    buttons->add(b);

}

Button Menu::removeButton(const std::string& id) {
    Button temp(id);
    buttons->remove(temp);
    return temp;
}

void Menu::draw(RenderWindow& w) {
    std::vector<Button> buttonList = buttons->query(boundary);
    for (Button b : buttonList) {
        b.draw(w);
    }
}

void Menu::click(Vector2f mousePos) {

}


