#include <iostream>
#include <vector>
#include <ctime>

//#include "Player.h"
#include "Snake.h"
#include "Food.h"






int main()
{
    std::shared_ptr<RenderWindow>window =
        std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "SFML works!");

    //test
    bool have = false;

    //head
    Snake snake(window);
    
    for (int i = 0; i < 50; i++)
        snake.addUnit();
    //food
    srand(time(0));
    FoodData data;
    data.pos = { float(rand() % WIDTH), float(rand() % HEIGHT) };
    data.size = SOC * 2 / 3;
    Food food(window, std::make_unique<FoodData>(data));

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
        snake.event();

        //logic
        snake.logic(time);
        //пересечение еды со змеёй

        //draw
        window->clear();

        food.draw();
        snake.draw();

        window->display();
    }

    return 0;
}
