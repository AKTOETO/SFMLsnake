#pragma once
#include <map>
#include <memory>

// �������, ���� ���� �������������� ������ BaseScene
#include "../../../scenes/GameScene/GameScene.h"
#include "../../../scenes/GameOverScene/GameOverScene.h"

#include "../BaseManager.h"

namespace Engine
{
	enum class Scenes
	{
		Start = 0,
		Game,
		GameOver,
	};

	class SceneManager : public BaseManager
	{
		std::pair<Scenes, std::unique_ptr<BaseScene>> m_cur_scene;

	public:
		//SceneManager(std::shared_ptr<RenderWindow> window);
		SceneManager(std::shared_ptr<Engine::Context>);
		~SceneManager();

		void setScene(Scenes, std::unique_ptr<BaseScene>);
		void processEvent();
		int processLogic(float) override;

		BaseScene& getCurScene() const;
	};
}

