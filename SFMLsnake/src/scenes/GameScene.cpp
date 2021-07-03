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

SceneData GameScene::processLogic(float time)
{
	m_snake->processLogic(time);
	m_food->processLogic(time);
	m_text->processLogic(time);
	m_text->setString("score: " + std::to_string(m_snake->getSize()));
	eatingFood();
	SceneData sdata;
	sdata.need_to_switch = false;
	return sdata;
}

void GameScene::processDraw()
{
	m_snake->processDraw();
	m_food->processDraw();
	m_text->processDraw();
}

void GameScene::eatingFood()
{
	if (SupportFunc::intersectRectangleShape((*m_snake)[0]->getRectangleShape(), m_food->getRectangleShape()))
	{
		m_snake->addUnit((*m_snake)[m_snake->getSize() - 1]->getPos());
		m_food->setPos({
			float(rand() % (WIDTH - SOC * 2 / 3)) + SOC / 3,
			float(rand() % (HEIGHT - SOC * 2 / 3)) + SOC / 3
			});
	}
}

 

