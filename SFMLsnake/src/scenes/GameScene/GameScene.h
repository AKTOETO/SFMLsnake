#pragma once
#include <memory>


#include "../BaseScene.h"
#include "../../Engine/objects/Text/Text.h"
#include "../../objects/Snake/Snake.h"
#include "../../objects/Food/Food.h"

class GameScene : public Engine::BaseScene
{
private:
	std::shared_ptr<Snake> m_snake;
	std::shared_ptr<Food> m_food;
	std::shared_ptr<Engine::TextObject> m_text;

public:
	GameScene(std::shared_ptr<Engine::Context>);

	int processLogic(float) override;

	void eatingFood();
};
