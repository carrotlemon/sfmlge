#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace sf;

int main()
{
    // Initialize window
    sf::RenderWindow window(sf::VideoMode(1440, 1080), "SFML works!");

    // Initialize green circle
    sf::CircleShape shape(100.f);
    sf::Texture texture;
    shape.setFillColor(sf::Color::Green);

    // Player vars
    float x;
    float y;

    // Mouse cursor to shrimp
    if (!texture.loadFromFile("shrimp.png")) {
        std::cout << "error loading image" << std::endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Grid of lines spaced 64 pixels apart
    std::vector<RectangleShape> lines;
    for (int i = 0; i < window.getSize().y; i += 64) {
        RectangleShape line(Vector2f(window.getSize().x, 2.f));
        line.setFillColor(Color::Magenta);
        line.setPosition(0, i);
        lines.push_back(line);
    }
    for (int i = 0; i < window.getSize().x; i += 64) {
        RectangleShape line(Vector2f(window.getSize().y, 2.f));
        line.setFillColor(Color::Magenta);
        line.setPosition(i, 0);
        line.setRotation(90);
        lines.push_back(line);
    }

    // File Writing
    std::ofstream MyFile("filename.txt");
    MyFile << "it works! good job";
    MyFile << "this is the second line";
    MyFile.close(); // close clears from memory space to clean up
    
    // File Reading
    std::string str;
    std::ifstream MyReadFile("filename.txt");
    while (getline(MyReadFile, str)) {
        std::cout << str;
    }
    MyReadFile.close();

    while (window.isOpen())
    {
        // Window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update cursor position
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        sprite.setPosition(mousepos.x-(int)(texture.getSize().x/2), mousepos.y- (int)(texture.getSize().y / 2));

        // Draw stuff
        window.clear();

        window.draw(shape);
        window.draw(sprite);
        for (RectangleShape line : lines) {
            window.draw(line);
        }

        window.display();
    }

    return 0;
}