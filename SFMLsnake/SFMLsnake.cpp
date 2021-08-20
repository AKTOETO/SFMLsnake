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
		std::make_shared<RenderWindow>(VideoMode(W_WIDTH, W_HEIGHT), "Snake");

	SceneManager sceneManager(window);
	sceneManager.setScene(Scenes::GameScene, std::make_unique<GameScene>(window));

	//////////////////////////////////////////////////////////
	std::unique_ptr<AnimationData> aData(new AnimationData);
	aData->animType = AnimationType::FOODSTAY;
	aData->offset = TextureOffset::RIGHT;
	aData->numberOfFrame = 4;
	aData->data.borders = IntRect(1, 1, 40, 40);
	aData->data.position = Vector2f(CENTER);
	std::shared_ptr<Texture> texture(new Texture);
	loadTexture(texture, "food.png");
	aData->data.texture = texture;
	aData->data.type = SpriteType::NONE;
	aData->data.size = Vector2f(4, 4);

	AnimatedPicture anim(aData);
	//////////////////////////////////////////////////////////


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
		anim.processLogic(time);

		//draw
		window->clear(Color::White);
		sceneManager.processDraw();
		window->draw(anim);
		window->display();
	}

	INFO("Bye bye!")
	return 0;
}