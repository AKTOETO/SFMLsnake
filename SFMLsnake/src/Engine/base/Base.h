#pragma once
#include "../Support.h"

namespace Engine
{
	// ������� ����� ��� ����� �������,
	// ������� ������ ����� ������ � ���������
	class Base
	{
	protected:
		// ��������
		std::shared_ptr<Engine::Context> m_context;

	public:
		/// <summary>
		/// ����������� ������
		/// </summary>
		/// <param name="context"> - ��������</param>
		Base(std::shared_ptr<Engine::Context> context) : m_context(context) {};
		~Base() {};
	};
}
