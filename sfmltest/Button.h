#pragma once

#include <iostream>
#include <functional>

class Button
{
private:
	std::function<void()> action;
public:
    Button(std::function<void()> a);
    void setAction(std::function<void()> func);
    void onClick();
};

