#pragma once
#include <memory>
#include <iostream>

#include "BaseObject.h"

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

class TextObject : public BaseObject
{
protected:
	std::unique_ptr<Text> m_text;
	std::shared_ptr<Font> m_font;
	std::unique_ptr<TextData> m_data;

public:
	TextObject(std::unique_ptr<TextData> data);
	~TextObject();

	virtual void processEvent() override;
	virtual int processLogic(float time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setString(std::string);
	void setPos(Vector2f);
};
