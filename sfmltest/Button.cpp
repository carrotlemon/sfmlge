#include "Button.h"

#include <iostream>
#include <functional>
#include <string>
#include "Box.h"

using namespace std;

// Constructors ----------------------------------------------------------------
Button::Button(const std::string& identity, const std::string& str, Vector2f p, Vector2f s, bool& b, std::function<void()> a) :
    id(identity), pos(p), size(s), action(a), toggle(b) {
    if (!texture.loadFromFile(str)) {}
    sprite.setTexture(texture);
}

Button::Button(const Button& other) : 
    id(other.id), pos(other.pos), size(other.size), action(other.action), toggle(other.toggle) {
    texture = other.texture;
    sprite = other.sprite;
}

// Set ----------------------------------------------------------------
void Button::setAction(std::function<void()> func) {
    action = func;
}

// Method that calls the stored function
bool Button::click() {
    if (action) { // Check if a function is set
        action();
        toggle = !toggle;
        return true;
    }
    else {
        std::cout << "No function set for this instance.\n";
    }
    return false;
}

// Get methods ----------------------------------------------------------------
quadtree::Box<float> Button::getBoundingBox() const {
    return quadtree::Box<float>(pos.x, pos.y, size.x, size.y);
}

// Other ----------------------------------------------------------------
bool Button::equals(const Button& other) const {
    return id == other.id;
  }

void Button::draw(RenderWindow& w) {
    sprite.setPosition(pos);
    w.draw(sprite);
}

std::ostream& operator<< (std::ostream& os, const Button& v) {
    return os << "Button " << v.id << ": X " << v.pos.x << " Y " << v.pos.x << " W " << v.size.x << " H " << v.size.x;
}