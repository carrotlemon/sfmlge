#include "Button.h"

#include <iostream>
#include <functional>
#include "Box.h"

using namespace std;

Button::Button(const std::string& identity, const std::string& str, Vector2f p, Vector2f s, std::function<void()> a) : 
    id(identity), pos(p), size(s), action(a) {
    if (!texture.loadFromFile(str)) {}
    sprite.setTexture(texture);
}

void Button::setAction(std::function<void()> func) {
    action = func;
}

// Method that calls the stored function
void Button::onClick() {
    if (action) { // Check if a function is set
        action();
    }
    else {
        std::cout << "No function set for this instance.\n";
    }
}

quadtree::Box<float> Button::getBoundingBox() const {
    return quadtree::Box<float>(pos.x, pos.y, size.x, size.y);
}

bool Button::equals(const Button& other) const {
    return id == other.id;
}