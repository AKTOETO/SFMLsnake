#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "src/objects/SceneManager/SceneManager.h"
#include "src/objects/Picture/Picture.h"

int main()
{
	std::shared_ptr<RenderWindow>window =
		std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "Snake");

	/*SceneManager sceneManager(window);
	sceneManager.setScene(Scenes::GameScene, std::make_unique<GameScene>(window));*/

	Picture pic;
	std::unique_ptr<SpriteData> data(new SpriteData);
	data->angle = 0;
	data->borders = IntRect(1, 1, 20, 20);
	data->originInCenter = true;
	data->position = Vector2f(100, 100);
	data->scale = Vector2f(1000, 1000);
	data->type = SpriteType::SNAKE;

	pic.addData<SpriteData>(data);

	Clock clock;
	long long counter = 0;
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
		//sceneManager.processEvent();

		//sceneManager.processLogic(time);

		//draw
		window->clear();
		//sceneManager.processDraw();
		window->draw(pic);
		window->display();
	}

	std::cout << "Bye bye!\n";
	return 0;
}