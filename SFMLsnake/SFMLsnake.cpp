#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "src/objects/SceneManager/SceneManager.h"

#include"src/objects/Picture/Picture.h"

int main()
{
	std::shared_ptr<RenderWindow>window =
		std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "Snake");

	/*SceneManager sceneManager(window);
	sceneManager.setScene(Scenes::GameScene, std::make_unique<GameScene>(window));*/

	SpriteData s_data;
	s_data.position = Vector2f(100, 100);
	s_data.borders = IntRect(1, 1, 20, 20);

	Picture pic(std::make_unique<SpriteData>(s_data));

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
		//sceneManager.processEvent();

		//sceneManager.processLogic(time);

		//draw
		window->clear();
		window->draw(pic);
		//sceneManager.processDraw();
		window->display();
	}

	std::cout << "Bye bye!\n";
	return 0;
}