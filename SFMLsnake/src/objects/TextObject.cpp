#include "TextObject.h"

TextObject::TextObject(std::shared_ptr<RenderWindow> window, TextData data)
{
	m_window = window;
	m_data = data;
	if (!m_font.loadFromFile("assets/fonts/" + m_data.font))
	{
		std::cout << "ERROR: can`t load: " << m_data.font;
	}

	m_text.setFont(m_font);
	m_text.setString(m_data.text);
	m_text.setCharacterSize(m_data.size);
	m_text.setFillColor(m_data.color);
	m_text.setStyle(m_data.styles);
	if (m_data.originInCeneter == true)
		m_text.setOrigin(
			m_text.getLocalBounds().width / 2,
			m_text.getLocalBounds().height / 2
		);
	m_text.setPosition(m_data.pos);
}

TextObject::~TextObject()
{
}

void TextObject::processEvent()
{
}

void TextObject::processLogic(float time)
{
}

void TextObject::processDraw()
{
	m_window->draw(m_text);
}

void TextObject::setString(std::string str)
{
	m_text.setString(str);
}

void TextObject::setPos(Vector2f pos)
{
	m_text.setPosition(pos);
}