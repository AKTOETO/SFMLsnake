#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<Engine::Context> context)
	:BaseScene(context)
{
	INFO("game scene const")
	//snake
	m_snake = std::make_unique<Snake>(m_context);

	//food
	srand(time(0));
	FoodData fData;
	fData.size = Vector2f(20, 20);
	fData.pos = {
		float(rand() % (W_WIDTH - 20 * 2 / 3)) + 20 / 3,
		float(rand() % (W_HEIGHT - 20 * 2 / 3) + 20 / 3)
	};
	m_food = std::make_unique<Food>(m_context, std::make_unique<FoodData>(fData));

	//text
	Engine::TextData tData;
	tData.pos = { 10, 0 };
	tData.size = 50;
	tData.originInCeneter = false;
	tData.text = "score:";

	m_text = std::make_unique<Engine::TextObject>
		(context, std::make_unique<Engine::TextData>(tData));

	m_objectList.push_back(m_text);
	m_objectList.push_back(m_food);
	m_objectList.push_back(m_snake);
}

int GameScene::processLogic(float time) 
{
	BaseScene::processLogic(time);
	if (m_snake->getAlive() == false)
	{
		need_to_switch = true;
	}
	m_text->setString("score: " + std::to_string(m_snake->getSize() - 3));
	eatingFood();
	return 0;
}

void GameScene::eatingFood()
{
	if (Engine::SupportFunc::intersectRectShapes(
		(*m_snake)[0]->getRectangleShape(), m_food->getRectangleShape()))
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