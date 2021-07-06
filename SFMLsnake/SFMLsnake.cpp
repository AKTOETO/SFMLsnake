#include <iostream>
#include <string>
#include <vector>
#include <ctime>

//#include "src/scenes/GameScene.h"
#include "src/objects/SceneManager/SceneManager.h"


int main()
{
    std::shared_ptr<RenderWindow>window =
        std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "Snake");

    //GameScene game(window);
    SceneManager sceneManager(window);
    sceneManager.setScene(Scenes::GameScene, std::make_unique<GameScene>(window));

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
            }
        }
        //snake.event();
        sceneManager.processEvent();

        sceneManager.processLogic(time);

        //draw
        window->clear();
        sceneManager.processDraw();
        window->display();
    }

    std::cout << "Bye bye!\n";
    return 0;
}
