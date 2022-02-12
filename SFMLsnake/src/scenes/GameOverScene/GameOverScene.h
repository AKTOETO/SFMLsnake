#pragma once
#include <memory>

#include "../BaseScene.h"
#include "../../objects/Text/Text.h"

class GameOverScene : public BaseScene
{
private:
	std::shared_ptr<TextObject> m_text;

public:
	GameOverScene(std::shared_ptr<RenderWindow>);
};

