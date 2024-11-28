#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include "Box.h"
#include "QuadTree.h"
#include "Button.h"

using namespace sf;

// Constructor for empty menu (no menu open)
Menu::Menu() :
    id(""), pos(Vector2f(0, 1)), size(Vector2f(1, 1)) {
    boundary = { 0, 0, 1, 1 };
    buttons = new quadtree::QuadTree<Button,
        std::function<quadtree::Box<float>(const Button&)>,
        std::function<bool(const Button&, const Button&)>>(
        boundary,
        [](const Button& b) {return b.getBoundingBox(); },
        [](const Button& a, const Button& b) {return a.equals(b); }
    );
}

Menu::Menu(const std::string& identity, Vector2f p, Vector2f s) : 
        id(identity), pos(p), size(s) {
    boundary = {p.x, p.y, s.x, s.y};
    buttons = new quadtree::QuadTree<Button,
        std::function<quadtree::Box<float>(const Button&)>,
        std::function<bool(const Button&, const Button&)>>(
        boundary,
        [](const Button& b) {return b.getBoundingBox(); },
        [](const Button& a, const Button& b) {return a.equals(b); }
    );
}

// Change list ----------------------------------------------------------------
void Menu::addButton(const Button& b) {
    buttons->add(b);

}

//Button Menu::removeButton(const std::string& id) {
//    bool b;
//    Button temp(id, "", Vector2f(0, 0), Vector2f(1, 1), b, []() {});
//    buttons->remove(temp);
//    return temp;
//}

// Action ----------------------------------------------------------------
void Menu::click(Vector2i mousePos) {
    std::vector<Button> clicked = buttons->findValuesAtPoint((float)mousePos.x, (float)mousePos.y);
    for (Button b : clicked) {
        b.click();
    }
}

// Other ----------------------------------------------------------------
bool Menu::equals(const Menu& other) const {
    return id == other.id;
}

void Menu::draw(RenderWindow& w) {
    std::vector<Button> buttonList = buttons->query(boundary);
    for (Button b : buttonList) {
        b.draw(w);
    }
}