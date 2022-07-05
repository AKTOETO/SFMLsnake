#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "../Engine/objects/BaseObject.h"


namespace Engine
{
	// ������� ����� ���� ����
	class BaseScene : public Base
	{
	protected:
		// ������ �������� �� �����
		std::list<std::shared_ptr<BaseObject>> m_objectList;
		// ���� ����������� ��� ������������ ����
		bool need_to_switch = false;

	public:
		/// <summary>
		/// ����������� 
		/// </summary>
		/// <param name="context"> - ��������</param>
		BaseScene(std::shared_ptr<Context> context);

		// ����������� ����������
		virtual ~BaseScene();

		// ������� ��������� �����
		virtual void activate();

		// ��� ����� ������ �������
		// ������� ��������� �������
		virtual void processEvent();
		// ������� ��������� ������
		virtual int processLogic(float);
		// ������� ��������� ��������
		virtual void processDraw();

		// ��������� ��������� ����� need_to_switch
		// ���� �� true - ����������� �����
		bool getNeedToSwitch() const { return need_to_switch; }
	};
}