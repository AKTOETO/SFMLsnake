#include "Snake.h"

Snake::Snake(std::shared_ptr<RenderWindow> window)
{
	m_window = window;
	CellData data;
	data.head = true;
	m_units.push_back(std::make_unique<Cell>(m_window, std::make_unique<CellData>(data)));

	data.color = Color::Red;
	data.size = { SOC * 2 / 3, SOC };
	data.head = false;
	data.pos = Vector2f(m_units[0]->getPos().x, m_units[0]->getPos().y + m_units[0]->getSize().x - 4);
	m_units.push_back(std::make_unique<Cell>(m_window, std::make_unique<CellData>(data)));

	data.pos = Vector2f(m_units[1]->getPos().x, m_units[1]->getPos().y + m_units[1]->getSize().x);
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

RSnakeData Snake::processLogic(float time)
{
	RSnakeData rSdata;
	for (int i = m_units.size() - 1; i > 0; i--)
	{
		//should the tail move
		m_units[i]->setDirection(m_units[i - 1]->getDirection());

		//calculate the logic at a sufficient distance
		if (
			sqrt(
				pow(m_units[i]->getPos().x - m_units[i - 1]->getPos().x, 2) +
				pow(m_units[i]->getPos().y - m_units[i - 1]->getPos().y, 2)
			) > (m_units[i]->getSize().y / 2 + m_units[i - 1]->getSize().y / 2) - OBC
			)
			m_units[i]->setPos(m_units[i - 1]->getPos());


		if (SupportFunc::intersectRectangleShape(
			m_units[0]->getCollisionShape(), m_units[i]->getRectangleShape())
			)
		{
			std::cout << m_units.size() - i <<
				" pieces were eaten (head and tail collision) <Snake.cpp>\n";
			m_units.erase(m_units.begin() + i, m_units.end());
		}

	}

	for (int i = m_units.size() - 1; i >= 0; i--)
	{
		RCellData rCdata;
		rCdata = m_units[i]->logic(time);
		if (i == 0 && rCdata.wallCollision == true)
		{
			rSdata.isAlive = false;
		}
		/*if (i == 1)
		{
			std::cout << "rotation: " << rCdata.rotation << " delta X: " <<
				rCdata.deltaX << " delta Y: " << rCdata.deltaY << std::endl;
		}*/
	}
	return rSdata;
}

void Snake::processDraw()
{
	for (int i = m_units.size() - 1; i >= 0; i--)
	{
		m_units[i]->draw();
	}
	m_units[0]->draw();
}

void Snake::addUnit(Vector2f pos, float rotation)
{
	CellData data;
	data.color = Color::Red;
	data.size = { SOC * 2 / 3, SOC };
	data.head = false;
	data.pos = std::move(pos);
	data.rotation = rotation;
	m_units.push_back(std::make_unique<Cell>(m_window, std::make_unique<CellData>(data)));
}

int Snake::getSize()
{
	return m_units.size();
}
