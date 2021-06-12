#pragma once
#include <memory>

#include "BaseScene.h"
#include "../objects/Snake.h"
#include "../objects/Food.h"
#include "../../Support.h"

class GameScene : public BaseScene
{
private:
	std::shared_ptr<RenderWindow> m_window;
	std::unique_ptr<Snake> snake;
	std::unique_ptr<Food> food;
	//std::vector<std::unique_ptr<BaseObject>> m_objectList;

public:
	GameScene(std::shared_ptr<RenderWindow>);
	~GameScene();

	void activate();

	void processEvent();
	void processLogic(float);
	void processDraw();

	void eatingFood();
};

