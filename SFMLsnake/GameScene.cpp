#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<RenderWindow> window)
	:m_window(window)
{
	//snake
	snake = std::make_unique<Snake>(m_window);

	//food
	srand(time(0));
	FoodData data;
	data.size = SOC * 2 / 3;
	data.pos = { 
		float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
		float(rand() % (HEIGHT - SOC * 2 / 3) + SOC / 3)
	};
	food = std::make_unique<Food>(window, std::make_unique<FoodData>(data));
}

GameScene::~GameScene()
{
}

void GameScene::activate()
{
}

void GameScene::processEvent()
{
	snake->event();
	food->event();
}

void GameScene::processLogic(float time)
{
	snake->logic(time);
	food->logic(time);
	eatingFood();
}

void GameScene::processDraw()
{
	snake->draw();
	food->draw();
}

void GameScene::eatingFood()
{
	if (SupportFunc::intersectRectangleShape((*snake)[0]->getRectangleShape(), food->getRectangleShape()))
	{
		snake->addUnit((*snake)[snake->size() - 1]->getPos());
		food->setPos({ float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
					  float(rand() % (HEIGHT - SOC * 2 / 3) + SOC / 3) });
	}
}

 

