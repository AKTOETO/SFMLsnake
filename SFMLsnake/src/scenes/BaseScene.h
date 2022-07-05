#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "../Engine/objects/BaseObject.h"


namespace Engine
{
	// Базовый класс всех сцен
	class BaseScene : public Base
	{
	protected:
		// список объектов на сцене
		std::list<std::shared_ptr<BaseObject>> m_objectList;
		// флаг необходимый для переключения сцен
		bool need_to_switch = false;

	public:
		/// <summary>
		/// Конструктор 
		/// </summary>
		/// <param name="context"> - контекст</param>
		BaseScene(std::shared_ptr<Context> context);

		// Виртуальный деструктор
		virtual ~BaseScene();

		// функция активации сцены
		virtual void activate();

		// Три самые важные функции
		// процесс получения событий
		virtual void processEvent();
		// процесс обработки логики
		virtual int processLogic(float);
		// процесс отрисовки объектов
		virtual void processDraw();

		// получение состояния флага need_to_switch
		// если он true - переключаем сцену
		bool getNeedToSwitch() const { return need_to_switch; }
	};
}