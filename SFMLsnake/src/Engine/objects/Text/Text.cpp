#include "Text.h"

namespace Engine
{
	TextObject::TextObject(std::unique_ptr<TextData> data)
		:m_font(new Font), m_text(new Text)
	{
		m_data = std::move(data);
		if (!m_font->loadFromFile("assets/fonts/" + m_data->font))
			ERROR("can't load: "+ m_data->font);

		m_text->setFont(*m_font);
		m_text->setString(m_data->text);
		m_text->setCharacterSize(m_data->size);
		m_text->setFillColor(m_data->color);
		m_text->setStyle(m_data->styles);
		if (m_data->originInCeneter == true)
			m_text->setOrigin(
				m_text->getLocalBounds().width / 2,
				m_text->getLocalBounds().height / 2
			);
		m_text->setPosition(m_data->pos);
	}

	TextObject::~TextObject()
	{
		m_text.reset(nullptr);
		m_font.reset();
		m_data.reset(nullptr);
	}

	void TextObject::processEvent()
	{
	}

	int TextObject::processLogic(float time)
	{
		return 0;
	}

	void TextObject::draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(*m_text, states);
	}

	void TextObject::setString(std::string str)
	{
		m_text->setString(str);
	}

	void TextObject::setPos(Vector2f pos)
	{
		m_text->setPosition(pos);
	}
}
