#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

namespace Engine
{
	// handle консоли
	const static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// цвета для консоли
	// черный
#define STDCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 7));
	// желтый
#define INFOCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 6));
	// красный
#define ERRORCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 4));
	// зеленый
#define HIGHLITER SetConsoleTextAttribute(h, ((0 << 4) | 2));

	class Logger
	{
	private:

	public:

#define TSTR(arg) std::to_string(arg)
		// информация о функции, вызывающей логгер.
		// msg - сообщение для вывода
#define FINFO(msg) __FILE__+ std::string(";")+__FUNCTION__+ std::string(";")+TSTR(__LINE__)+ std::string(";")+msg//TSTR(__FILE__+";"+TSTR(__FUNCTION__) +";"+TSTR(__LINE__)+";"+msg)

		/// <summary>
		/// конструктор, изначально длеает черный фон консоли
		/// </summary>
		Logger();

		/// <summary>
		/// Вывод информации в консоль
		/// </summary>
		/// <param name="data"> - принимает FINFO</param>
		void info(std::string data);

		/// <summary>
		/// Вывод критической ошибки в консоль
		/// </summary>
		/// <param name="data"> - принимает FINFO </param>
		void crit(std::string data);

	};		
}
