#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "../objects/BaseObject.h"

namespace Engine
{
	class BaseScene
	{
	protected:
		std::shared_ptr<RenderWindow> m_window;
		std::list<std::shared_ptr<BaseObject>> m_objectList;
		bool need_to_switch = false;

	public:
		BaseScene(std::shared_ptr<RenderWindow> window);
		virtual ~BaseScene();

		virtual void activate();

		virtual void processEvent();
		virtual int processLogic(float);
		virtual void processDraw();

		bool getNeedToSwitch() const { return need_to_switch; }
	};
}