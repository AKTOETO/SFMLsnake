#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<RenderWindow> window)
	:m_window(window)
{

	//snake
	m_snake = std::make_unique<Snake>(m_window);

	//food
	srand(time(0));
	FoodData f_data;
	f_data.size = SOC * 2 / 3;
	f_data.pos = {
		float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
		float(rand() % (HEIGHT - SOC * 2 / 3) + SOC / 3)
	};
	m_food = std::make_unique<Food>(window, std::make_unique<FoodData>(f_data));

	//text
	TextData t_data;
	t_data.pos = { 10, 0 };
	t_data.size = 50;
	t_data.originInCeneter = false;
	t_data.text = "score:";

	m_text = std::make_unique<TextObject>(m_window, t_data);
}

GameScene::~GameScene()
{
}

void GameScene::activate()
{
}

void GameScene::processEvent()
{
	m_snake->processEvent();
	m_food->processEvent();
	m_text->processEvent();
}

RSceneData GameScene::processLogic(float time)
{
	RSceneData sdata;
	RSnakeData rsnake = m_snake->processLogic(time);
	if (rsnake.isAlive == false)
	{
		sdata.need_to_switch = true;
	}
	m_food->processLogic(time);
	m_text->processLogic(time);
	m_text->setString("score: " + std::to_string(m_snake->getSize()));
	eatingFood();
	return sdata;
}

void GameScene::processDraw()
{
	m_food->processDraw();
	m_snake->processDraw();
	m_text->processDraw();
}

void GameScene::eatingFood()
{
	if (SupportFunc::intersectRectangleShape((*m_snake)[0]->getRectangleShape(), m_food->getRectangleShape()))
	{
#define CELL(param) (*m_snake)[m_snake->getSize() - param]
		std::cout << "eat food (head and food collision) <GameScene.cpp>\n";
		if (m_snake->getSize() > 1)
			m_snake->addUnit(CELL(2)->getPos(), CELL(2)->getRotation());
		else
			m_snake->addUnit(CELL(1)->getPos(), CELL(1)->getRotation());

		m_food->setPos({
			float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
			float(rand() % (HEIGHT - SOC * 2 / 3)) + SOC / 3
			});
	}
}



