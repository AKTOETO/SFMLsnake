#include "Logger.h"

namespace Engine
{
	Logger::Logger()		
	{
		// консоль черного цвета
		STDCOLOR
	}

	/// <summary>
	/// Выделение слова из строки, разделенной с помощью delimeter
	/// </summary>
	/// <param name="str"> - строка с токенами</param>
	/// <param name="delimeter"> - символы, разделяющие токены (их может быт несколько)</param>
	/// <returns> токен </returns>
	std::string getToken(std::string& str, std::string delimeter = ";")
	{
		// позиция разделяющего символа delimeter
		int pos_of_delim = str.find_first_of(delimeter);

		// строка, которая позже выведется в консоль
		std::string out_str = str.substr(0, pos_of_delim);

		// удаление строки, которая выведется в консоль +
		// удаление символа delimeter, если строка str не кончилась
		str.erase(str.begin(), str.begin() + (pos_of_delim != -1 ? pos_of_delim + 1: 0));

		return out_str;
	}

	void highlithing(std::string str, int width)
	{
#ifdef _DEBUG
		HIGHLITER
			std::cout << std::setfill(' ') << std::setw(width) << '<' + str.substr(str.find_last_of("\\") + 1) + '>';
		STDCOLOR
#endif
	}

	/// <summary>
	/// Функция определяет текущее время
	/// </summary>
	/// <returns> Возвращает текущее время hh:mm::ss</returns>
	std::string currTime()
	{
#ifdef _DEBUG
		time_t rawtime;
		struct tm* timeinfo = new tm;

		time(&rawtime);
		localtime_s(timeinfo, &rawtime);

		return TSTR(timeinfo->tm_hour) + ":" + TSTR(timeinfo->tm_min) + ":" + TSTR(timeinfo->tm_sec);
#else
		return std::string();
#endif
	}

	void Logger::info(std::string data)
	{
		std::string log_data = data;

		INFOCOLOR
			std::cout << "[INFO]";
		STDCOLOR

		std::cout << " (" << currTime() << ") [file: ";
		highlithing(getToken(log_data), 22);
		std::cout << "] [function: ";
		highlithing(getToken(log_data), 37);
		std::cout << "] [line: ";
		highlithing(getToken(log_data), 5);
		std::cout << "] [message: ";
		highlithing(getToken(log_data), 0);
		std::cout << "]\n";

	}
	void Logger::crit(std::string data)
	{
		std::cout << "criterr\n";
		std::exit(1);
	}
}