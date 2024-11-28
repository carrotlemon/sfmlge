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
#include "MapBuilder.h"

using namespace sf;

int main()
{
    // Initialize window ----------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1440, 1080), "SFML works!");

    // Camera ----------------------------------------------------------------
    // create a view with its center and size
    Vector2f wsize = (Vector2f)window.getSize();
    sf::View view(sf::Vector2f(wsize.x / 2, wsize.y / 2), wsize);
    window.setView(view);

    // Clock ----------------------------------------------------------------
    Clock clock;
    bool paused = true;
    Menu currentMenu; // default menu does nothing
    bool pausedthistime = false;
    bool m1Toggle = false;

    // Main Menu ----------------------------------------------------------------
    Button startButton("start", "startButton.png", Vector2f((float)window.getSize().x / 2 - 128, 
        (float)window.getSize().y / 3 - 128), Vector2f(256, 128), paused, []() {});
    Menu mainMenu("mainmenu", Vector2f(0, 0), (Vector2f)window.getSize());
    mainMenu.addButton(startButton);
    currentMenu = mainMenu;
    // Paused Game Menu ----------------------------------------------------------------
    Button resumeButton("pause", "xButton.png", Vector2f(50, 50), Vector2f(256, 256), paused,
        []() {});
    Menu pausedMenu("testMenu", Vector2f(0, 0), Vector2f(1080, 1440));
    pausedMenu.addButton(resumeButton);

    Menu noMenu("nomenu", Vector2f(0, 0), Vector2f(1080, 1440));

    
    
    // Mouse shrimp to cursor ----------------------------------------------------------------
    sf::Texture texture1;
    if (!texture1.loadFromFile("shrimp64.png")) {
        std::cout << "error loading image" << std::endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture1);

    // Block and Room test ----------------------------------------------------------------
    Room room("roomname", Vector2f(0, 0), Vector2f(window.getSize()));
    Block block(Vector2f(256, 256), Vector2f(64, 64), std::string("sprites/grass.png"));
    room.addBlock(block);
    Block block2(Vector2f(320, 256), Vector2f(64, 64), std::string("sprites/grass.png"));
    room.addBlock(block2);
    Block block3(Vector2f(384, 256), Vector2f(64, 64), 0);
    block3.setHitBoxToggle(false);
    room.addBlock(block3);
    room.addBlock(Block(Vector2f(512, 256), Vector2f(64, 64), 0, true));

    std::vector<Block> blist = fill(Vector2f(448, 512), Vector2f(64, 64), Vector2i(3, 3), 0, false);
    room.addBlocks(blist);

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
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Update cursor position
        Vector2i mousepos = Mouse::getPosition(window);
        sprite.setPosition(window.mapPixelToCoords(Vector2i((float)mousepos.x - (texture1.getSize().x / 2), (float)mousepos.y - (texture1.getSize().y / 2))));

        // Universal Controls
        // t flip flop now
        if (Keyboard::isKeyPressed(Keyboard::Scan::Escape)) {
            if (!pausedthistime) {
                paused = !paused;
                if (paused)
                    currentMenu = pausedMenu;
                else
                    currentMenu = noMenu;
                pausedthistime = true;
            }
        }
        else {
            pausedthistime = false;
        }

        if (currentMenu.equals(noMenu) && !paused) { // Only move when game is not paused
            // Movement Controls
            velocity = movementControls(speed);

            // Horizontal Movement
            velocity.x *= dt.asSeconds();
            float maxX = moveUntilCollision(room, 0, velocity.x, player.getPos(), player.getSize(), true);
            player.move(Vector2f(maxX, 0));

            // Vertical Movement
            velocity.y *= dt.asSeconds();
            float maxY = moveUntilCollision(room, 0, velocity.y, player.getPos(), player.getSize(), false);
            player.move(Vector2f(0, maxY));

        } else {
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                if (!m1Toggle) {
                    currentMenu.click(Mouse::getPosition(window));
                    if (!paused)
                        currentMenu = noMenu;
                    m1Toggle = true;
                }
            }
            else {
                m1Toggle = false;
            }
        }

        // Update Camera
        view.setCenter(player.getPos());
        window.setView(view);

        // Draw stuff
        window.clear();

        //window.draw(shape);
        room.draw(window);

        player.draw(window);

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