#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

const static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

#define STDCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 7));
#define INFOCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 6));
#define ERRORCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 4));
#define HIGHLITER SetConsoleTextAttribute(h, ((0 << 4) | 2));

static void curTime()
{
	time_t rawtime;
	struct tm* timeinfo = new tm;

	time(&rawtime);
	localtime_s(timeinfo, &rawtime);

#define FW std::setfill('0') << std::setw(2)
	std::cout << FW << timeinfo->tm_hour << ':' << FW << timeinfo->tm_min << ':' << FW << timeinfo->tm_sec;
}

static std::ofstream cout("log/log.txt", std::ios::out);

static void infoSetting()
{
	INFOCOLOR
		std::cout << "[INFO]";
	STDCOLOR
}

static void errorSetting()
{
	ERRORCOLOR
		std::cout << "[ERROR]";
	STDCOLOR
}

static void highlithing(std::string str, int width)
{
	HIGHLITER
		std::cout << std::setfill(' ') << std::setw(width) << '<' + str.substr(str.find_last_of("\\") + 1) + '>';
	STDCOLOR
}

#define TEMPLATE(str){\
	std::cout << " (";\
	curTime();\
	std::cout << ") [file: ";\
	highlithing(std::string(__FILE__), 22);\
	std::cout << "] [function: ";\
	highlithing(std::string(__FUNCTION__), 37);\
	std::cout<< "] [line: ";\
	highlithing(std::to_string(__LINE__), 5);\
	std::cout << "] [message: ";\
	highlithing(str, 0);\
	std::cout<<"]\n";\
}

#define INFO(str){\
	infoSetting();\
	TEMPLATE(str);\
}

#define ERROR(str){\
	errorSetting();\
	TEMPLATE(str);\
}
