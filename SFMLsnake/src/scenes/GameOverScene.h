#pragma once
#include <memory>

#include "BaseScene.h"
#include "../objects/TextObject.h"

class GameOverScene : public BaseScene
{
private:
	std::unique_ptr<TextObject> m_text;

public:
	GameOverScene(std::shared_ptr<RenderWindow>);
	~GameOverScene() override;

	virtual void activate() override;
	virtual void deactivate() override;

	virtual void processEvent() override;
	virtual int processLogic(float) override;
	virtual void processDraw() override;
};

