#include "SceneManager.h"

SceneManager::SceneManager(std::shared_ptr<RenderWindow> window)
	:m_window(window)
{
	INFO("sc manager constructor")
	m_cur_scene = std::make_pair<Scenes, std::unique_ptr<BaseScene>>(Scenes::Start, nullptr);
}

SceneManager::~SceneManager()
{
	INFO("sc manager destructor")
}

void SceneManager::setScene(Scenes id_scene, std::unique_ptr<BaseScene> scene)
{
	INFO("id new scene " + std::to_string(int(id_scene)))
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
		m_cur_scene.second->processLogic(time);
		if (m_cur_scene.second->getNeedToSwitch() == true)
		{
			switch (m_cur_scene.first)
			{
				INFO("switch scene")
			case Scenes::Start:
				setScene(Scenes::Game, std::make_unique<GameScene>(m_window));
				break;

			case Scenes::Game:
				setScene(Scenes::GameOver, std::make_unique<GameOverScene>(m_window));
				break;

			default:
				break;
			}
		}
	}
	else
	{
		ERROR("the scene does not exist")
	}
}

void SceneManager::processDraw()
{
	if (m_cur_scene.second != nullptr)
	{
		m_cur_scene.second->processDraw();
	}
}