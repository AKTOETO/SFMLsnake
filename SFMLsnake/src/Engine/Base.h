#pragma once
#include "Support.h"

namespace Engine
{
	// Базовый класс для любых классов,
	// которые должны иметь доступ к контексту
	class Base : public Drawable
	{
	protected:
		// контекст
		std::shared_ptr<Engine::Context> m_context;

	public:
		/// <summary>
		/// Конструктор класса
		/// </summary>
		/// <param name="context"> - контекст</param>
		Base(std::shared_ptr<Engine::Context> context) : m_context(context) {};
		~Base() {};

		virtual void draw(RenderTarget& target, RenderStates states) const {};
	};
}
