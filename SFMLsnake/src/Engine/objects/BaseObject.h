#pragma once
//#include "../Support.h"
#include "../baseDrawable/BaseDrawable.h"

namespace Engine
{
	// ������� ����� �������,
	// ������� ������ �������������� �� �����
	class BaseObject : public BaseDrawable
	{
	public:
		/// <summary>
		/// �����������, ���������� ����������� ������ Base
		/// </summary>
		/// <param name="context"> - ��������, ������������ � ����������� Base</param>
		BaseObject(std::shared_ptr<Engine::Context> context): BaseDrawable(context) {};
		// ����������
		~BaseObject() {};

		// ������� ��������� �������
		virtual void processEvent() = 0;
		// ������� ��������� ������
		virtual int processLogic(float time) = 0;
		// ������� ��������� ��������
		// ��������� ���������� � ������� ��������
		// ����� ������� � window.draw()
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	};
}
