#include "Food.h"

Food::Food(std::shared_ptr<RenderWindow> window, std::unique_ptr<FoodData> data)
	:m_window(window)
{
	m_data = std::move(data);
	m_rect.setSize({ m_data->size, m_data->size });
	m_rect.setOrigin(m_rect.getLocalBounds().width / 2,
		m_rect.getLocalBounds().height / 2);
	m_rect.setPosition(m_data->pos);
	m_rect.setFillColor(m_data->color);
}

Food::~Food()
{
}

void Food::event()
{
}

void Food::logic(float time)
{
}

void Food::draw()
{
	m_window->draw(m_rect);
}

void Food::setPos(Vector2f pos)
{
	m_rect.setPosition(pos);
}
