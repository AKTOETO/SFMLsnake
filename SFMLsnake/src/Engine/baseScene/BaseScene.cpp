#include "BaseScene.h"
#pragma once
namespace Engine
{
	BaseScene::BaseScene(std::shared_ptr<Context> context)
		:m_context(context)
	{
	}

#define FORALL for (auto it = m_objectList.begin(); it != m_objectList.end(); it++)

	BaseScene::~BaseScene()
	{
		FORALL
		(*it).reset();
		INFO("base scene destructor")
	}

	void BaseScene::activate()
	{
		INFO("base scene activate")
	}

	void BaseScene::processEvent()
	{
		FORALL
		(*it)->processEvent();
	}

	int BaseScene::processLogic(float time)
	{
		FORALL
		(*it)->processLogic(time);
		return 0;
	}

	void BaseScene::processDraw()
	{
		FORALL
		m_context->m_window->draw(*(*it));
	}
}