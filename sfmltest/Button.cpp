#include "Button.h"

#include <iostream>
#include <functional>
#include <string>
#include "Box.h"

using namespace std;

Button::Button(const std::string& identity) : 
    id(identity), pos(Vector2f(0, 0)), size(Vector2f(1, 1)) {

}

Button::Button(const std::string& identity, const std::string& str, Vector2f p, Vector2f s, std::function<void()> a) :
    id(identity), pos(p), size(s), action(a), toggle(false) {
    if (!texture.loadFromFile(str)) {}
    sprite.setTexture(texture);
}

void Button::setAction(std::function<void()> func) {
    action = func;
}

// Method that calls the stored function
bool Button::click() {
    if (action) { // Check if a function is set
        action();
        return true;
    }
    else {
        std::cout << "No function set for this instance.\n";
    }
    return false;
}

quadtree::Box<float> Button::getBoundingBox() const {
    return quadtree::Box<float>(pos.x, pos.y, size.x, size.y);
}

bool Button::equals(const Button& other) const {
    return id == other.id;
  }

void Button::draw(RenderWindow& w) {
    sprite.setPosition(pos);
    w.draw(sprite);
}