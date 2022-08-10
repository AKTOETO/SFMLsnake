#pragma once
#include "../base/Base.h"


namespace Engine
{
	/// <summary>
	/// ������� ����� ��� ����������
	/// </summary>
	class BaseManager : public Base
	{
	public:
		BaseManager(std::shared_ptr<Engine::Context> context):Base(context) {};
		~BaseManager() {};

		virtual int processLogic(float time) = 0;
	};
}