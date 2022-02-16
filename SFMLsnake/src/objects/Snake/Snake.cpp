#include "Snake.h"

Snake::Snake(std::shared_ptr<RenderWindow> window)
{
	INFO("snake constructor")
	CellData data;
	data.head = true;
	m_units.push_back(std::make_unique<Cell>(std::make_unique<CellData>(data)));

	data.color = Color::Red;
	data.size = { 12, 40 };
	data.head = false;
	data.pos = Vector2f(m_units[0]->getBackPos().x,
		m_units[0]->getBackPos().y + m_units[0]->getSize().y / 2);
	m_units.push_back(std::make_unique<Cell>(std::make_unique<CellData>(data)));

	data.pos = Vector2f(m_units[1]->getBackPos().x,
		m_units[1]->getBackPos().y + m_units[1]->getSize().y / 2);
	m_units.push_back(std::make_unique<Cell>(std::make_unique<CellData>(data)));
}

Snake::~Snake()
{
	INFO("snake destructor")
	m_units.clear();
}

std::unique_ptr<Cell>& Snake::operator[](int i)
{
	return m_units[i];
}

void Snake::processEvent()
{
	for (int i = 0; i < m_units.size(); i++)
	{
		m_units[i]->processEvent();
	}
}

int Snake::processLogic(float time)
{
	for (int i = m_units.size() - 1; i > 0; i--)
	{
		//should the tail move
		m_units[i]->setDirection(m_units[i - 1]->getDirection());

		//calculate the logic at a sufficient distance
		if (
			sqrt(
					pow(m_units[i]->getBackPos().x - m_units[i - 1]->getFrontPos().x, 2) +
					pow(m_units[i]->getBackPos().y - m_units[i - 1]->getFrontPos().y, 2)
				) > OBC
			)
			m_units[i]->setPos(m_units[i - 1]->getBackPos());

		if (
			Engine::SupportFunc::intersectRectShapePoint(
				m_units[0]->getCollisionPoint(), m_units[i]->getRectangleShape()
			)
			&& i != 1 && i != 2
			) 
		{
			INFO(std::to_string(m_units.size() - i) + " pieces were eaten")
			m_units.erase(m_units.begin() + i, m_units.end());
		}
	}

	for (int i = m_units.size() - 1; i >= 0; i--)
	{
		m_units[i]->processLogic(time);
		//эта информация должна получаться из Cell через метод getStatus

		//эта информация должна возвращаться через метод getStatus
		if (m_units[i]->getWallCollision() == true)
		{
			m_isAlive = false;
		}
	}
	return 0;
}

void Snake::draw(RenderTarget& target, RenderStates states) const
{
	for (int i = m_units.size() - 1; i >= 0; i--)
	{
		target.draw(*m_units[i]);
	}
	target.draw(*m_units[0]);
}

void Snake::addUnit(Vector2f pos, float rotation)
{
	INFO("added unit")
	CellData data;
	data.color = Color::Red;
	data.size = { 12, 40 };
	data.head = false;
	data.pos = std::move(pos);
	data.rotation = rotation;
	m_units.push_back(std::make_unique<Cell>(std::make_unique<CellData>(data)));
}

int Snake::getSize()
{
	return m_units.size();
}

bool Snake::getAlive()
{
	return m_isAlive;
}
