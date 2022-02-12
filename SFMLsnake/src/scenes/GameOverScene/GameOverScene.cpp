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

	m_objectList.push_back(m_text);
}