#include "BaseScene.h"
#pragma once
namespace Engine
{
	BaseScene::BaseScene(std::shared_ptr<RenderWindow> window)
		:m_window(window)
	{
	}

	BaseScene::~BaseScene()
	{
		for (auto it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			(*it).reset();
		}
		INFO("base scene destructor")
	}

	void BaseScene::activate()
	{
		INFO("base scene activate")
	}

	void BaseScene::processEvent()
	{
		for (auto it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			(*it)->processEvent();
		}
	}

	int BaseScene::processLogic(float time)
	{
		for (auto it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			(*it)->processLogic(time);
		}
		return 0;
	}

	void BaseScene::processDraw()
	{
		for (auto it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			m_window->draw(*(*it));
		}
	}
}