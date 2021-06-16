#include "Snake.h"

Snake::Snake(std::shared_ptr<RenderWindow> window)
{
	m_window = window;
	CellData data;
	data.head = true;
	m_units.push_back(std::make_unique<Cell>(m_window, std::make_unique<CellData>(data)));
}

Snake::~Snake()
{
}

std::unique_ptr<Cell>& Snake::operator[](int i)
{
	return m_units[i];
}


void Snake::processEvent()
{

	for (int i = 0; i < m_units.size(); i++)
	{
		m_units[i]->event();
	}
}

void Snake::processLogic(float time)
{
	for (int i = m_units.size() - 1; i > 0; i--)
	{
		if(
			sqrt(
				pow(m_units[i]->getPos().x - m_units[i - 1]->getPos().x, 2) +
				pow(m_units[i]->getPos().y - m_units[i - 1]->getPos().y, 2)
				) > (m_units[i]->getSize().x / 2 + m_units[i - 1]->getSize().x) - OBC
			)
		m_units[i]->setNewPos(m_units[i - 1]->getPos());

	}



	for (int i = m_units.size() - 1; i > 0; i--)
	{
		m_units[i]->logic(time);
	}
	m_units[0]->logic(time);

}

void Snake::processDraw()
{
	for (int i = m_units.size() - 1; i >= 0; i--)
	{
		m_units[i]->draw();
	}
	m_units[0]->draw();
}

void Snake::addUnit(Vector2f pos)
{
	CellData data;
	data.color = Color::Red;
	data.size = SOC * 2 / 3;
	data.head = false;
	data.pos = pos;

	m_units.push_back(std::make_unique<Cell>(m_window, std::make_unique<CellData>(data)));
	std::cout << "size: " << m_units.size() << std::endl;
}

int Snake::getSize()
{
	return m_units.size();
}
