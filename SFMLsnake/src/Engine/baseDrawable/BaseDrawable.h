#pragma once
#include "../base/Base.h"

namespace Engine
{
	// Базовый класс для любых классов,
	// которые должны иметь доступ к контексту 
	// и возможность отрисовываться
	class BaseDrawable : public Base, public Drawable
	{
	public:
		/// <summary>
		/// Конструктор класса
		/// </summary>
		/// <param name="context"> - контекст</param>
		BaseDrawable(std::shared_ptr<Engine::Context> context) : Base(context) {};
		~BaseDrawable() {};

		/// <summary>
		/// Функция орисовки объекта
		/// </summary>
		/// <param name="target"> - куда отрисовывать</param>
		/// <param name="states"> - состояния отрисовки</param>
		virtual void draw(RenderTarget& target, RenderStates states) const {};
	};
}
