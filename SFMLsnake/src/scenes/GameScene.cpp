#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<RenderWindow> window)
	:BaseScene(window)
{
	INFO("game constructor")
	//snake
	m_snake = std::make_unique<Snake>(m_window);

	//food
	srand(time(0));
	FoodData fData;
	fData.size = Vector2f(20, 20);
	fData.pos = {
		float(rand() % (W_WIDTH - 20 * 2 / 3)) + 20 / 3,
		float(rand() % (W_HEIGHT - 20 * 2 / 3) + 20 / 3)
	};
	m_food = std::make_unique<Food>(window, std::make_unique<FoodData>(fData));

	//text
	TextData tData;
	tData.pos = { 10, 0 };
	tData.size = 50;
	tData.originInCeneter = false;
	tData.text = "score:";

	m_text = std::make_unique<TextObject>(std::make_unique<TextData>(tData));

	m_objects.push_back(m_snake);
}

GameScene::~GameScene()
{
	INFO("game destructor")
	deactivate();
}

void GameScene::activate()
{
}

void GameScene::deactivate()
{
	m_snake.reset();
	m_food.reset();
	m_text.reset();
	for (auto n : m_objects)
	{
		n.reset();
	}
}

void GameScene::processEvent()
{
	m_snake->processEvent();
	m_food->processEvent();
	m_text->processEvent();
}

int GameScene::processLogic(float time)
{
	m_snake->processLogic(time);
	if (m_snake->getAlive() == false)
	{
		need_to_switch = true;
	}
	m_food->processLogic(time);
	m_text->processLogic(time);
	m_text->setString("score: " + std::to_string(m_snake->getSize()));
	eatingFood();
	return 0;
}

void GameScene::processDraw()
{
	m_window->draw(*m_text);
	m_window->draw(*m_food);
	m_window->draw(*m_snake);
}

void GameScene::eatingFood()
{
	if (SupportFunc::intersectRectShapes((*m_snake)[0]->getRectangleShape(), m_food->getRectangleShape()))
	{
		INFO("eat food")
#define CELL(param) (*m_snake)[m_snake->getSize() - param]
		if (m_snake->getSize() > 1)
			m_snake->addUnit(CELL(2)->getBackPos(), CELL(2)->getRotation());
		else
			m_snake->addUnit(CELL(1)->getBackPos(), CELL(1)->getRotation());

		m_food->setPos({
			float(rand() % (W_WIDTH - 20 * 2 / 3)) + 20 / 3,
			float(rand() % (W_HEIGHT - 20 * 2 / 3)) + 20 / 3
			});
	}
}