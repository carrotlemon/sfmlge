#include "Button.h"

#include <iostream>
#include <functional>

using namespace std;

Button::Button(std::function<void()> a) {
    action = a;
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