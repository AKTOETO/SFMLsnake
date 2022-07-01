#pragma once
//#include "../Support.h"
#include "../Base.h"

namespace Engine
{
	// Базовый класс объекта,
	// которые должны отрисовываться на сцене
	class BaseObject : public Base
	{
	public:
		/// <summary>
		/// Конструктор, вызывающий конструктор класса Base
		/// </summary>
		/// <param name="context"> - контекст, передаваемый в конструктор Base</param>
		BaseObject(std::shared_ptr<Engine::Context> context): Base(context) {};
		// Деструктор
		~BaseObject() {};

		// Три самые важные функции
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
