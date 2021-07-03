#include "SceneManager.h"

SceneManager::SceneManager(std::shared_ptr<RenderWindow> window)
	:m_window(window)
{
	m_cur_scene = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::setScene(std::unique_ptr<BaseScene> scene)
{
	m_cur_scene = std::move(scene);
}

void SceneManager::processEvent()
{
	if (m_cur_scene != nullptr)
	{
		m_cur_scene->processEvent();
	}
}

void SceneManager::processLogic(float time)
{
	if (m_cur_scene != nullptr)
	{
		m_cur_scene->processLogic(time);
	}
}

void SceneManager::processDraw()
{
	if (m_cur_scene != nullptr)
	{
		m_cur_scene->processDraw();
	}
}
