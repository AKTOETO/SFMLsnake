#pragma once
#include "../base/Base.h"

namespace Engine
{
	// ������� ����� ��� ����� �������,
	// ������� ������ ����� ������ � ��������� 
	// � ����������� ��������������
	class BaseDrawable : public Base, public Drawable
	{
	public:
		/// <summary>
		/// ����������� ������
		/// </summary>
		/// <param name="context"> - ��������</param>
		BaseDrawable(std::shared_ptr<Engine::Context> context) : Base(context) {};
		~BaseDrawable() {};

		/// <summary>
		/// ������� �������� �������
		/// </summary>
		/// <param name="target"> - ���� ������������</param>
		/// <param name="states"> - ��������� ���������</param>
		virtual void draw(RenderTarget& target, RenderStates states) const {};
	};
}
