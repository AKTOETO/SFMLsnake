#pragma once
#include <map>
#include <memory>

// костыль, надо чтоб импортировался только BaseScene
#include "../../../scenes/GameScene/GameScene.h"
#include "../../../scenes/GameOverScene/GameOverScene.h"

namespace Engine
{
	enum class Scenes
	{
		Start = 0,
		Game,
		GameOver,
	};

	class SceneManager
	{
		std::shared_ptr<Context> m_context;
		std::pair<Scenes, std::unique_ptr<BaseScene>> m_cur_scene;

	public:
		//SceneManager(std::shared_ptr<RenderWindow> window);
		SceneManager(std::shared_ptr<Context>);
		~SceneManager();

		void setScene(Scenes, std::unique_ptr<BaseScene>);
		void processEvent();
		void processLogic(float);
		void processDraw();
	};
}

