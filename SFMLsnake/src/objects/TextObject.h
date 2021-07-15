#pragma once
#include <memory>
#include <iostream>

#include "../../Support.h"

struct TextData
{
	std::string font = "main.ttf";
	std::string text = "test";
	int size = 20;
	Color color = Color::Green;
	Uint32 styles = sf::Text::Bold;
	Vector2f pos = { 10, 10 };
	bool originInCeneter = false;
};

class TextObject
{
private:
	std::shared_ptr<RenderWindow> m_window;
	Text m_text;
	Font m_font;
	TextData m_data;

public:
	TextObject(std::shared_ptr<RenderWindow>, TextData data);
	~TextObject();

	void processEvent();
	void processLogic(float time);
	void processDraw();

	void setString(std::string);
	void setPos(Vector2f);
};
