#pragma once
#include <memory>

#include "../BaseScene.h"
#include "../../objects/Snake/Snake.h"
#include "../../objects/Food/Food.h"
#include "../../objects/Text/Text.h"

class GameScene : public BaseScene
{
private:
	std::shared_ptr<Snake> m_snake;
	std::shared_ptr<Food> m_food;
	std::shared_ptr<TextObject> m_text;

public:
	GameScene(std::shared_ptr<RenderWindow>);

	int processLogic(float) override;

	void eatingFood();
};
