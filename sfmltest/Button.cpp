#include "Button.h"

#include <iostream>
#include <functional>
#include "Box.h"

using namespace std;

Button::Button()
{

}

Button::Button(const std::string& identity) : 
    id(identity) {

}

Button::Button(const std::string& identity, const std::string& str, Vector2f p, Vector2f s, std::function<void()> a) : 
    id(identity), pos(p), size(s), actionNone(a) {
    if (!texture.loadFromFile(str)) {}
    sprite.setTexture(texture);
}

void Button::setAction(std::function<void()> func) {
    actionNone = func;
}

// Method that calls the stored function
void Button::click() {
    if (actionNone) { // Check if a function is set
        actionNone();
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

void Button::draw(RenderWindow& w) {
    sprite.setPosition(pos);
    w.draw(sprite);
}