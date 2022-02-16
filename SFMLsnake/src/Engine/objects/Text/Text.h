#pragma once
#include <memory>
#include <iostream>

#include "../BaseObject.h"

namespace Engine
{
	struct TextData
	{
		std::string font = "main.ttf";
		std::string text = "test";
		int size = 20;
		Color color = Color::Green;
		Uint32 styles = Text::Bold;
		Vector2f pos = { 10, 10 };
		bool originInCeneter = false;

	};

	class TextObject : public BaseObject
	{
	protected:
		std::unique_ptr<Text> m_text;
		std::shared_ptr<Font> m_font;
		std::unique_ptr<TextData> m_data;

	public:
		TextObject(std::unique_ptr<TextData> data);
		~TextObject();

		void processEvent() override;
		int processLogic(float time) override;
		void draw(RenderTarget& target, RenderStates states) const override;

		void setString(std::string);
		void setPos(Vector2f);
	};
}

