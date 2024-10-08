﻿#include <iostream>
#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "Observer.hpp"
#include "Raycasting.hpp"

int main()
{
    // win2d initalization and configuration
    sf::RenderWindow window2d(sf::VideoMode(800, 600), "2D drawing");
    window2d.setPosition(sf::Vector2i(1100, 150));
    window2d.setFramerateLimit(90);


    // win3d initalization and configuration
    sf::RenderWindow window3d(sf::VideoMode(WindowSizeX, WindowSizeY), "3D visualization");
    window3d.setPosition(sf::Vector2i(50, 150));
    window3d.setFramerateLimit(90);

    // Classes
        //3D Floor and roof
        sf::RectangleShape roof;
        roof.setFillColor(sf::Color(54, 52, 102));
        roof.setPosition(sf::Vector2f(0, 0));
        roof.setSize(sf::Vector2f(WindowSizeX, WindowSizeY/2));

        sf::RectangleShape floor;
        floor.setFillColor(sf::Color(43, 43, 84));
        floor.setPosition(sf::Vector2f(0, WindowSizeY / 2));
        floor.setSize(sf::Vector2f(WindowSizeX, WindowSizeY / 2));
     
        //Block
        sf::RectangleShape block;
        block.setFillColor(sf::Color(55, 55, 55));
        block.setSize(sf::Vector2f(BlockSize, BlockSize));


        std::vector<sf::Vector2f> blocks_positions;

        for (short y = 0; y < WorldY; y++){
            for (short x = 0; x < WorldX; x++) {
                if (WorldMap[y][x] != 0) {
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
            observer.take_event(event3d);
        }

        window3d.clear();
        window3d.draw(roof);
        window3d.draw(floor);
        raycasting.draw3d(window3d);
        window3d.display();
    }

    return 0;
}