﻿#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "src/managers/SceneManager/SceneManager.h"

int main()
{
	INFO("start game")

	// creating a window
	std::shared_ptr<RenderWindow>window(new RenderWindow(VideoMode(W_WIDTH, W_HEIGHT), "Snake"));

	// creating a scene Manager
	SceneManager sceneManager(window);
	sceneManager.setScene(Scenes::Game, std::make_unique<GameScene>(window));

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
		sceneManager.processEvent();

		//logic
		sceneManager.processLogic(time);

		//draw
		window->clear();
		sceneManager.processDraw();
		window->display();
	}

	INFO("Bye bye!")
		return 0;
}