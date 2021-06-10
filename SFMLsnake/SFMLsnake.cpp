﻿#include <iostream>
#include <vector>
#include <memory>

#include "Player.h"






int main()
{
    std::shared_ptr<RenderWindow>window =
        std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "SFML works!");


    //head
    Head hd(window);

    Clock clock;
    while (window->isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        //events
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window->close();
        }
        hd.event();

        //logic
        hd.logic(time);

        //draw
        window->clear();

        hd.draw();

        window->display();
    }

    return 0;
}
