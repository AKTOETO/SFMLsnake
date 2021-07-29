#include "GameOverScene.h"

GameOverScene::GameOverScene(std::shared_ptr<RenderWindow> window)
	:BaseScene(window)
{
	TextData tData;
	tData.pos = { WIDTH / 2, HEIGHT / 2 };
	tData.size = 70;
	tData.originInCeneter = true;
	tData.color = Color::Yellow;
	tData.text = "game over";
	m_text = std::make_unique<TextObject>(m_window, tData);
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
	m_text->processDraw();
}
