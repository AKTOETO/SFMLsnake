#pragma once
#include <memory>

#include "BaseScene.h"
#include "../objects/TextObject.h"
#include "../../Support.h"

class GameOverScene : public BaseScene
{
private:
	std::unique_ptr<TextObject> m_text;

public:
	GameOverScene(std::shared_ptr<RenderWindow>);
	~GameOverScene() override;

	void activate() override;
	void deactivate() override;

	void processEvent() override;
	RSceneData processLogic(float) override;
	void processDraw() override;
};

