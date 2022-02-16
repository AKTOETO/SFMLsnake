#pragma once
#include "../Support.h"

namespace Engine
{
	class BaseObject : public Drawable
	{
	protected:

	public:
		BaseObject() {};
		~BaseObject() {};

		virtual void processEvent() = 0;
		virtual int processLogic(float time) = 0;
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	};
}
