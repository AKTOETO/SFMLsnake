#include "GameOverScene.h"

GameOverScene::GameOverScene(std::shared_ptr<Engine::Context> context)
	:BaseScene(context)
{
	Engine::TextData tData;
	tData.pos = { W_WIDTH / 2, W_HEIGHT / 2 };
	tData.size = 70;
	tData.originInCeneter = true;
	tData.color = Color::Yellow;
	tData.text = "game over";
	m_text = std::make_unique<Engine::TextObject>
		(context, std::make_unique<Engine::TextData>(tData));

	m_objectList.push_back(m_text);
}