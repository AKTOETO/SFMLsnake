#include <iostream>
#include <string>
#include <vector>
#include <ctime>

//#include "Player.h"
#include "Snake.h"
#include "Food.h"


bool intersectRectangleShape(RectangleShape f, RectangleShape s)
{
//#define GB(param) f.getGlobalBounds().param
    if (f.getGlobalBounds().intersects(s.getGlobalBounds()) == 1)
    {
        return true;
    }
    return false;
}



int main()
{
    std::shared_ptr<RenderWindow>window =
        std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "Snake");

    //head
    Snake snake(window);
    
    //food
    srand(time(0));
    FoodData data;
    data.size = SOC * 2 / 3;
    data.pos = { float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
                 float(rand() % (HEIGHT - SOC * 2 / 3) + SOC / 3) };
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
            {
                window->close();
                std::cout << "Bye bye!\n";
            }
        }
        snake.event();

        //logic
        snake.logic(time);

        //eating food
        if (intersectRectangleShape(snake[0]->getRectangleShape(), food.getRectangleShape()))
        {
            snake.addUnit(snake[snake.size() - 1]->getPos());            
            food.setPos({ float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
                          float(rand() % (HEIGHT - SOC * 2 / 3) + SOC / 3) });
        }

        //draw
        window->clear();

        food.draw();
        snake.draw();

        window->display();
    }

    return 0;
}
