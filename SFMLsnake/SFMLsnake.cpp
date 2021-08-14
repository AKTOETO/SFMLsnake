#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "src/objects/SceneManager/SceneManager.h"
#include "src/objects/Picture/AnimatedPicture.h"

int main()
{
	INFO("start game")

	std::shared_ptr<RenderWindow>window =
		std::make_shared<RenderWindow>(VideoMode(WIDTH, HEIGHT), "Snake");

	SceneManager sceneManager(window);
	sceneManager.setScene(Scenes::GameScene, std::make_unique<GameScene>(window));

	std::unique_ptr<AnimationData> aData(new AnimationData);
	aData->animType = AnimationType::FOODSTAY;
	aData->numberOfFrame = 4;
	aData->data.borders = IntRect(1, 1, 40, 40);
	aData->data.position = Vector2f(WIDTH / 2, HEIGHT / 2);
	std::shared_ptr<Texture> texture(new Texture);
	loadTexture(texture, "food.png");
	aData->data.texture = texture;
	aData->data.type = SpriteType::NONE;
	aData->data.size = Vector2f(10, 10);

	AnimatedPicture aPic(aData);

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

		sceneManager.processLogic(time);
		aPic.processLogic(time);

		//draw
		window->clear(Color::White);
		window->draw(aPic);
		sceneManager.processDraw();
		window->display();
	}

	INFO("Bye bye!")
	return 0;
}