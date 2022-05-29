#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

namespace Engine
{
	// handle �������
	const static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// ����� ��� �������
	// ������
#define STDCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 7));
	// ������
#define INFOCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 6));
	// �������
#define ERRORCOLOR SetConsoleTextAttribute(h, ((0 << 4) | 4));
	// �������
#define HIGHLITER SetConsoleTextAttribute(h, ((0 << 4) | 2));

	class Logger
	{
	private:

	public:

#define TSTR(arg) std::to_string(arg)
		// ���������� � �������, ���������� ������.
		// msg - ��������� ��� ������
#define FINFO(msg) __FILE__+ std::string(";")+__FUNCTION__+ std::string(";")+TSTR(__LINE__)+ std::string(";")+msg//TSTR(__FILE__+";"+TSTR(__FUNCTION__) +";"+TSTR(__LINE__)+";"+msg)

		/// <summary>
		/// �����������, ���������� ������ ������ ��� �������
		/// </summary>
		Logger();

		/// <summary>
		/// ����� ���������� � �������
		/// </summary>
		/// <param name="data"> - ��������� FINFO</param>
		void info(std::string data);

		/// <summary>
		/// ����� ����������� ������ � �������
		/// </summary>
		/// <param name="data"> - ��������� FINFO </param>
		void crit(std::string data);

	};		
}
