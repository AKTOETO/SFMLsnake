#include "SceneManager.h"

SceneManager::SceneManager(std::shared_ptr<RenderWindow> window)
	:m_window(window)
{
	m_cur_scene = std::make_pair<Scenes, std::unique_ptr<BaseScene>>(Scenes::StartScene, nullptr);
}

SceneManager::~SceneManager()
{
}

void SceneManager::setScene(Scenes id_scene, std::unique_ptr<BaseScene> scene)
{
	//m_cur_scene = std::make_pair<Scenes, std::unique_ptr<BaseScene>>(id_scene, std::move(scene));
	m_cur_scene.first = id_scene;
	m_cur_scene.second = std::move(scene);
}

void SceneManager::processEvent()
{
	if (m_cur_scene.second != nullptr)
	{
		m_cur_scene.second->processEvent();
	}
}

void SceneManager::processLogic(float time)
{
	if (m_cur_scene.second != nullptr)
	{
		RSceneData rscene = m_cur_scene.second->processLogic(time);
		if (rscene.need_to_switch == true)
		{
			switch (m_cur_scene.first)
			{
			case Scenes::StartScene:
				setScene(Scenes::GameScene, std::make_unique<GameScene>(m_window));

				break;

			case Scenes::GameScene:
				setScene(Scenes::GameOver, std::make_unique<GameOverScene>(m_window));

				break;

			default:
				break;
			}
		}
	}
}

void SceneManager::processDraw()
{
	if (m_cur_scene.second != nullptr)
	{
		m_cur_scene.second->processDraw();
	}
}