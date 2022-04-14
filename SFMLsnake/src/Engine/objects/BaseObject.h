#pragma once
#include "../Support.h"

namespace Engine
{
	class BaseObject : public Drawable
	{
	protected:
		std::shared_ptr<Engine::Context> m_context;

	public:
		BaseObject() {};
		BaseObject(std::shared_ptr<Engine::Context> obj): m_context(obj) {};
		~BaseObject() {};

		virtual void processEvent() = 0;
		virtual int processLogic(float time) = 0;
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	};
}
