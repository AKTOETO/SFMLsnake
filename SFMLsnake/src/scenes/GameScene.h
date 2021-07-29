#pragma once
#include <memory>

#include "BaseScene.h"
#include "../objects/Snake.h"
#include "../objects/Food.h"
#include "../objects/TextObject.h"
#include "../../Support.h"

class GameScene : public BaseScene
{
private:
	std::shared_ptr<RenderWindow> m_window;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
	std::unique_ptr<TextObject> m_text;

public:
	GameScene(std::shared_ptr<RenderWindow>);
	~GameScene() override;

	void activate() override;
	void deactivate() override;

	void processEvent() override;
	RSceneData processLogic(float) override;
	void processDraw() override;

	void eatingFood();
};
