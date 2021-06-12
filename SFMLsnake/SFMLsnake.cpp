#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "src/scenes/GameScene.h"


int main()
{
    std::shared_ptr<RenderWindow>window =
        std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "Snake");

    GameScene game(window);

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
            {
                window->close();
                std::cout << "Bye bye!\n";
            }
        }
        //snake.event();
        game.processEvent();

        game.processLogic(time);

        //draw
        window->clear();
        game.processDraw();
        window->display();
    }

    return 0;
}
