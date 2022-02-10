#pragma once
#include <memory>
#include <list>

#include "BaseScene.h"
#include "../objects/Snake.h"
#include "../objects/Food.h"
#include "../objects/TextObject.h"

class GameScene : public BaseScene
{
private:
	std::shared_ptr<Snake> m_snake;
	std::shared_ptr<Food> m_food;
	std::shared_ptr<TextObject> m_text;

	std::list<std::shared_ptr<BaseObject>> m_objects;

public:
	GameScene(std::shared_ptr<RenderWindow>);
	~GameScene() override;

	virtual void activate() override;
	virtual void deactivate() override;

	virtual void processEvent() override;
	virtual int processLogic(float) override;
	virtual void processDraw() override;

	void eatingFood();
};
