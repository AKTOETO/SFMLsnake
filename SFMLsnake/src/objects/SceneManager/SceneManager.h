#pragma once
#include <map>
#include <memory>

#include "../../../Support.h"
#include "../../../Logger.hpp"
#include "../../scenes/GameScene.h"
#include "../../scenes/GameOverScene.h"

enum class Scenes
{
	StartScene = 0,
	GameScene,
	GameOver,
};

class SceneManager
{
	std::shared_ptr<RenderWindow> m_window;
	std::pair<Scenes, std::unique_ptr<BaseScene>> m_cur_scene;

public:
	SceneManager(std::shared_ptr<RenderWindow> window);
	~SceneManager();

	void setScene(Scenes, std::unique_ptr<BaseScene>);
	void processEvent();
	void processLogic(float);
	void processDraw();
};
