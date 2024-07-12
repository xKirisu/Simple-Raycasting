#include <iostream>
#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "Observer.hpp"
#include "Raycasting.hpp"

int main()
{
    // win2d initalization and configuration
    sf::RenderWindow window2d(sf::VideoMode(800, 600), "2D drawing");

    // win3d initalization and configuration
    sf::RenderWindow window3d(sf::VideoMode(WindowSizeX, WindowSizeY), "3D visualization");

    // Classes
        //Block
        sf::RectangleShape block;
        block.setFillColor(sf::Color(55, 55, 55));
        block.setSize(sf::Vector2f(BlockSize, BlockSize));


        std::vector<sf::Vector2f> blocks_positions;

        for (short y = 0; y < WorldY; y++){
            for (short x = 0; x < WorldX; x++) {
                if (WorldMap[y][x] == 1) {
                    sf::Vector2f position(x * BlockSize, y * BlockSize);
                    blocks_positions.push_back(position);
                }
            }
        }

        //Observer
        rc::Observer observer(sf::Vector2f(300, 500));
        //Raycasting
        rc::Raycasting raycasting(observer.getPosition(), observer.getRotation());


    //Tickrate
    float tickrate;
    sf::Clock tick;

    //loop
    while (window2d.isOpen() && window3d.isOpen())
    {
        // 2D Window draw
        sf::Event event2d;
        while (window2d.pollEvent(event2d))
        {
            if (event2d.type == sf::Event::Closed)
                window2d.close();
            observer.take_event(event2d);
        }

        tickrate = tick.restart().asSeconds();
        raycasting.cast();
        observer.update(tickrate);

        window2d.clear();
        for (sf::Vector2f& position : blocks_positions) {
            block.setPosition(position);
            window2d.draw(block);
        }
        observer.draw(window2d);
        raycasting.draw2d(window2d);
        window2d.display();

        // 3D window draw
        sf::Event event3d;
        while (window3d.pollEvent(event3d))
        {
            if (event3d.type == sf::Event::Closed)
                window3d.close();
        }

        window3d.clear();
        raycasting.draw3d(window3d);
        window3d.display();
    }

    return 0;
}