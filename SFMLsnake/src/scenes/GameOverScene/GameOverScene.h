#pragma once
#include <memory>

#include "../BaseScene.h"
#include "../../Engine/objects/Text/Text.h"


class GameOverScene : public Engine::BaseScene
{
private:	
	std::shared_ptr<Engine::TextObject> m_text;

public:
	GameOverScene(std::shared_ptr<Engine::Context>);
};

