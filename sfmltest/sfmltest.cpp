#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "Block.h"
#include "Room.h"
#include "Player.h"

using namespace sf;

int main()
{
    // Initialize window
    sf::RenderWindow window(sf::VideoMode(1440, 1080), "SFML works!");
    
    // Mouse cursor to shrimp
    sf::Texture texture;
    if (!texture.loadFromFile("shrimp64.png")) {
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

    // Clock
    Clock clock;
    bool paused = false;
    bool pausedthistime = false;

    // Block and Room test
    Block block(Vector2f(250, 250), Vector2f(168, 168), std::string("shrimp.png"));
    std::vector<Block> blocklist;
    blocklist.push_back(block);
    Room room(blocklist);

    // Player vars
    float speed = 1000;
    Vector2f velocity(0, 0);
    Player player("shrimp64.png");
    player.setPos(Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    // Main Game Loop
    while (window.isOpen())
    {
        // Get Delta Time
        Time dt = clock.restart();

        // Window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Debug Prints
        //std::cout << block << std::endl << player << std::endl;

        // Update cursor position
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        sprite.setPosition(mousepos.x - (int)(texture.getSize().x / 2), mousepos.y - (int)(texture.getSize().y / 2));

        // Universal Controls
        // t flip flop now
        if (Keyboard::isKeyPressed(Keyboard::Scan::Escape)) {
            if (!pausedthistime) {
                paused = !paused;
                pausedthistime = true;
            }
        }
        else {
            pausedthistime = false;
        }

        if (!paused) {
            // Movement Controls
            velocity = Vector2f(0, 0);

            if (Keyboard::isKeyPressed(Keyboard::Scan::Right))
                velocity.x += speed;
            if (Keyboard::isKeyPressed(Keyboard::Scan::Left))
                velocity.x -= speed;
            if (Keyboard::isKeyPressed(Keyboard::Scan::Up))
                velocity.y -= speed;
            if (Keyboard::isKeyPressed(Keyboard::Scan::Down))
                velocity.y += speed;

            velocity.y *= dt.asSeconds();
            velocity.x *= dt.asSeconds();
            // if players new pos doesn't collide, move it
            if (!room.collides(Vector2f(player.getPos().x + velocity.x, player.getPos().y), player.getSize())) {
                player.move(Vector2f(velocity.x, 0));
            }
            if (!room.collides(Vector2f(player.getPos().x, player.getPos().y + velocity.y), player.getSize())) {
                player.move(Vector2f(0, velocity.y));
            }
        }
        else { // game paused

        }



        // Draw stuff
        window.clear();

        //window.draw(shape);
        room.draw(window);
        window.draw(sprite);
        for (RectangleShape line : lines) {
            window.draw(line);
        }
        player.draw(window);

        if (paused) {
            
        }

        window.display();
    }

    return 0;
}

//// File Writing
//std::ofstream MyFile("filename.txt");
//MyFile << "it works! good job";
//MyFile << "this is the second line";
//MyFile.close(); // close clears from memory space to clean up
//
//// File Reading
//std::string str;
//std::ifstream MyReadFile("filename.txt");
//while (getline(MyReadFile, str)) {
//    std::cout << str;
//}
//MyReadFile.close();