#include "GameOverScene.h"

GameOverScene::GameOverScene(std::shared_ptr<RenderWindow> window)
	:BaseScene(window)
{
	TextData tData;
	tData.pos = { W_WIDTH / 2, W_HEIGHT / 2 };
	tData.size = 70;
	tData.originInCeneter = true;
	tData.color = Color::Yellow;
	tData.text = "game over";
	m_text = std::make_unique<TextObject>(std::make_unique<TextData>(tData));
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::activate()
{
}

void GameOverScene::deactivate()
{
}

void GameOverScene::processEvent()
{
	m_text->processEvent();
}

RSceneData GameOverScene::processLogic(float)
{
	return RSceneData();
}

void GameOverScene::processDraw()
{
	m_window->draw(*m_text);
}
