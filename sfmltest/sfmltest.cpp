#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>

#include "Block.h"
#include "Room.h"
#include "Player.h"
#include "Button.h"
#include "QuadTree.h"
#include "Box.h"
#include "Menu.h"
#include "Misc.h"

using namespace sf;

struct Object { // example object for testing quadtree
    float x, y, width, height, id;

    quadtree::Box<float> getBoundingBox() const {
        return quadtree::Box<float>(x, y, width, height);
    }
};

int main()
{
    // Clock ----------------------------------------------------------------
    Clock clock;
    bool paused = false;
    Menu currentMenu; // default menu does nothing
    bool pausedthistime = false;
    bool m1Toggle = false;

    // Test Button ----------------------------------------------------------------
    Button b("test", "xButton.png", Vector2f(800, 800), Vector2f(256, 256),
        []() {std::cout << "button works"; });
    Button pauseButton("pause", "xButton.png", Vector2f(50, 50), Vector2f(256, 256),
        []() {  });
    Menu testMenu("testMenu", Vector2f(0, 0), Vector2f(1080, 1440));
    testMenu.addButton(b);
    Menu noMenu("", Vector2f(0, 0), Vector2f(1080, 1440));
    //b.onClick();

    // Initialize window ----------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1440, 1080), "SFML works!");
    
    // Mouse shrimp to cursor ----------------------------------------------------------------
    sf::Texture texture;
    if (!texture.loadFromFile("shrimp64.png")) {
        std::cout << "error loading image" << std::endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Grid of lines spaced 64 pixels apart ----------------------------------------------------------------
    std::vector<RectangleShape> lines;
    for (float i = 0; i < window.getSize().y; i += 64) {
        RectangleShape line(Vector2f((float)window.getSize().x, 2.f));
        line.setFillColor(Color::Magenta);
        line.setPosition(0, i);
        lines.push_back(line);
    }
    for (float i = 0; i < window.getSize().x; i += 64) {
        RectangleShape line(Vector2f((float)window.getSize().y, 2.f));
        line.setFillColor(Color::Magenta);
        line.setPosition(i, 0);
        line.setRotation(90);
        lines.push_back(line);
    }

    // Block and Room test ----------------------------------------------------------------
    Room room("roomname", Vector2f(0, 0), Vector2f(window.getSize()));
    Block block(Vector2f(256, 256), Vector2f(64, 64), std::string("sprites/grass.png"));
    room.addBlock(block);
    Block block2(Vector2f(320, 256), Vector2f(64, 64), std::string("sprites/grass.png"));
    room.addBlock(block2);
    Block block3(Vector2f(384, 256), Vector2f(64, 64), 0);
    block3.setHitBoxToggle(false);
    room.addBlock(block3);

    // Player vars ----------------------------------------------------------------
    float speed = 500;
    Vector2f velocity(0, 0);
    Player player("shrimp64.png");
    player.setPos(Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2));

    // Main Game Loop ----------------------------------------------------------------
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

        // Update cursor position
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        sprite.setPosition((float)mousepos.x - (texture.getSize().x / 2), (float)mousepos.y - (texture.getSize().y / 2));

        // Universal Controls
        // t flip flop now
        if (Keyboard::isKeyPressed(Keyboard::Scan::Escape)) {
            if (!pausedthistime) {
                paused = !paused;
                if (paused)
                    currentMenu = testMenu;
                else
                    currentMenu = noMenu;
                pausedthistime = true;
            }
        }
        else {
            pausedthistime = false;
        }

        if (!paused) {
            // Movement Controls
            velocity = movementControls(speed);

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
        
        for (RectangleShape line : lines) {
            window.draw(line);
        }
        player.draw(window);

        if (paused) {
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                if (!m1Toggle) {
                    currentMenu.click(Mouse::getPosition(window));
                    m1Toggle = true;
                }
            }
            else {
                m1Toggle = false;
            }
        }

        currentMenu.draw(window);
        window.draw(sprite);

        window.display();
    }

    return 0;
}

/*

*/

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