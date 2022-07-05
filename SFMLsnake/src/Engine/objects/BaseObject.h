#pragma once
//#include "../Support.h"
#include "../baseDrawable/BaseDrawable.h"

namespace Engine
{
	// Базовый класс объекта,
	// который должен отрисовываться на сцене
	class BaseObject : public BaseDrawable
	{
	public:
		/// <summary>
		/// Конструктор, вызывающий конструктор класса Base
		/// </summary>
		/// <param name="context"> - контекст, передаваемый в конструктор Base</param>
		BaseObject(std::shared_ptr<Engine::Context> context): BaseDrawable(context) {};
		// Деструктор
		~BaseObject() {};

		// процесс получения событий
		virtual void processEvent() = 0;
		// процесс обработки логики
		virtual int processLogic(float time) = 0;
		// процесс отрисовки объектов
		// отрисовка происходит с помощью передачи
		// этого объекта в window.draw()
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	};
}
