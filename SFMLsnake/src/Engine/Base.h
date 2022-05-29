#pragma once
#include "Support.h"

namespace Engine
{
	class Base : public Drawable
	{
	protected:
		std::shared_ptr<Engine::Context> m_context;

	public:
		Base(std::shared_ptr<Engine::Context> obj) : m_context(obj) {};
		~Base() {};
	};
}
