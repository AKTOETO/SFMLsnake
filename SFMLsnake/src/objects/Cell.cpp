#include "Cell.h"

Cell::Cell(std::shared_ptr<RenderWindow> window, std::unique_ptr<CellData> data)
	:m_window(window), m_sprite(new Picture), m_rect(new Picture)
{
	m_data = move(data);

	// ===== RECT DATA & RECT OBJECT =====
	std::unique_ptr<ShapeData> shData(new ShapeData);
	shData->size = m_data->size;
	shData->position = m_data->pos;
	shData->color = m_data->color;
	shData->angle = m_data->rotation;

	m_rect->addData<ShapeData>(shData);
	// =====================

	// ===== SPRITE DATA =====
	std::unique_ptr<SpriteData> sData(new SpriteData); //sData - sprite Data
	sData->position = { m_rect->getPosition() };
	// ===================

	// ===== COLLISION RECT DATA =====
	std::unique_ptr<ShapeData> crData(new ShapeData); //crData - collision rectangle Data
	// ===================

	//==========HEAD==========
	if (m_data->head == true)
	{
#define POSG(param) m_rect->getPosition().param

		m_collisionPoint = std::make_unique<Vector2f>(POSG(x), POSG(y) - m_data->size.y / 2);

		sData->borders = { 1, 1, 40, 40 };
	}
	else
	{
		//==========BODY==========
		sData->borders = { 1, 42, 40, 40 };
	}
	m_posBackPoint = std::make_unique<Vector2f>(
		sin(-m_rect->getRotation()) * m_data->size.x / 2 + POSG(x),
		cos(-m_rect->getRotation()) * m_data->size.y / 2 + POSG(y)
		);
	m_posFrontPoint = std::make_unique<Vector2f>(
		-sin(-m_rect->getRotation()) * m_data->size.x / 2 + POSG(x),
		-cos(-m_rect->getRotation()) * m_data->size.y / 2 + POSG(y)
		);

	m_sprite->addData<SpriteData>(sData);
}

Cell::~Cell()
{
}

void Cell::event()
{
#define PRESS(param) Keyboard::isKeyPressed(Keyboard::param)
	if (m_data->head == true && (PRESS(A) || PRESS(Left)) && m_dir != Direction::RIGHT)
		m_dir = Direction::LEFT;
	else if (m_data->head == true && (PRESS(W) || PRESS(Up)) && m_dir != Direction::DOWN)
		m_dir = Direction::UP;
	else if (m_data->head == true && (PRESS(D) || PRESS(Right)) && m_dir != Direction::LEFT)
		m_dir = Direction::RIGHT;
	else if (m_data->head == true && (PRESS(S) || PRESS(Down)) && m_dir != Direction::UP)
		m_dir = Direction::DOWN;
}

RCellData Cell::logic(float time)
{
	RCellData rdata;

#define POSFG(param) m_posFrontPoint->param
	//==========HEAD==========
	if (m_data->head == true)
	{
#define POSG(param) m_rect->getPosition().param
#define BOUND(param) float(m_rect->getScale().param)

		//collision with wall
		if (
			POSG(x) + BOUND(x) / 2 > WIDTH ||
			POSG(y) + BOUND(y) / 2 > HEIGHT ||
			POSG(x) - BOUND(x) / 2 < 0 ||
			POSG(y) - BOUND(y) / 2 < 0
			)
		{
			m_dir = Direction::STOP;
			rdata.wallCollision = true;
			std::cout << "game over (wall collision) <Cell.cpp>\n";
		}

		//head mooving
		if (m_dir == Direction::LEFT)
		{
			if (POSG(x) - BOUND(x) / 2 > 0)
			{
				m_rect->setPosition(Vector2f(POSG(x) - SPEED * time, POSG(y)));
			}
			else
			{
				m_rect->setPosition({ BOUND(x) / 2, POSG(y) });
			}

			//temp
			m_sprite->setRotation(270);
			m_rect->setRotation(270);
		}
		else if (m_dir == Direction::RIGHT)
		{
			if (POSG(x) + BOUND(x) / 2 < WIDTH)
			{
				m_rect->setPosition(Vector2f(POSG(x) + SPEED * time, POSG(y)));
			}
			else
			{
				m_rect->setPosition({ WIDTH - BOUND(x) / 2, POSG(y) });
			}

			//temp
			m_sprite->setRotation(90);
			m_rect->setRotation(90);
		}
		else if (m_dir == Direction::UP)
		{
			if (POSG(y) - BOUND(x) / 2 > 0)
			{
				m_rect->setPosition(Vector2f(POSG(x), POSG(y) - SPEED * time));
			}
			else
			{
				m_rect->setPosition({ POSG(x), BOUND(x) / 2 });
			}

			//temp
			m_sprite->setRotation(0);
			m_rect->setRotation(0);
		}
		else if (m_dir == Direction::DOWN)
		{
			if (POSG(y) + BOUND(x) / 2 < HEIGHT)
			{
				m_rect->setPosition(Vector2f(POSG(x), POSG(y) + SPEED * time));
			}
			else
			{
				m_rect->setPosition({ POSG(x), HEIGHT - BOUND(x) / 2 });
			}

			//temp
			m_sprite->setRotation(180);
			m_rect->setRotation(180);
		}

		//collision rectangle logic
		switch (m_dir)
		{
		case Direction::UP:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x), POSG(y) - BOUND(y) / 2));
			break;
		case Direction::DOWN:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x), POSG(y) + BOUND(y) / 2));
			break;
		case Direction::LEFT:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x) - BOUND(y) / 2, POSG(y)));
			break;
		case Direction::RIGHT:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x) + BOUND(y) / 2, POSG(y)));
			break;
		}
	}
	//==========BODY==========
	else
	{
		if (m_dir != Direction::STOP)
		{
			float k = 0.06; // smoothness of movement //0.1

			m_rect->setPosition(Vector2f(
				POSG(x) + ((m_newPos.x - POSFG(x)) * SPEED * time * k),
				POSG(y) + ((m_newPos.y - POSFG(y)) * SPEED * time * k)
			));

			rdata.deltaX = (m_newPos.x - POSG(x));
			rdata.deltaY = (m_newPos.y - POSG(y));

			if ((rdata.deltaX <= 0 and rdata.deltaY >= 0) or (rdata.deltaX >= 0 and rdata.deltaY >= 0))
			{
				m_rect->setRotation(
					(-std::atan((m_newPos.x - POSG(x)) / (m_newPos.y - POSG(y))) + PI) * 180 / PI
				);
			}
			else
			{
				m_rect->setRotation(
					-std::atan((m_newPos.x - POSG(x)) / (m_newPos.y - POSG(y))) * 180 / PI
				);
			}

			rdata.rotation = m_rect->getRotation();

			//temp
			m_sprite->setRotation(m_rect->getRotation());
		}
	}
	m_posBackPoint = std::make_unique<Vector2f>(
		sin(-m_rect->getRotation() * PI / 180) * (m_data->size.y / 2 - 10) + POSG(x),
		cos(-m_rect->getRotation() * PI / 180) * (m_data->size.y / 2 - 10) + POSG(y)
		);
	m_posFrontPoint = std::make_unique<Vector2f>(
		-sin(-m_rect->getRotation() * PI / 180) * (m_data->size.y / 2 - 10) + POSG(x),
		-cos(-m_rect->getRotation() * PI / 180) * (m_data->size.y / 2 - 10) + POSG(y)
		);

	//temp
	m_sprite->setPosition(m_rect->getPosition());

	return rdata;
}

void Cell::draw()
{
	//hit boxes
	if (SHB == true)
	{
		m_window->draw(*m_rect);
	}
	else
	{
		//sprite
		m_window->draw(*m_sprite);
	}
}

Vector2f Cell::getCollisionPoint()
{
	return *m_collisionPoint;
}

Vector2f Cell::getSize()
{
	return m_data->size;
}

Vector2f Cell::getBackPos()
{
	return *m_posBackPoint;
}

Vector2f Cell::getCenterPos()
{
	return m_rect->getPosition();
}

Vector2f Cell::getFrontPos()
{
	return *m_posFrontPoint;
}

void Cell::setDirection(Direction dir)
{
	m_dir = dir;
}

void Cell::setRotation(float rotation)
{
	m_rect->setRotation(rotation);
}

Direction Cell::getDirection()
{
	return m_dir;
}

float Cell::getRotation()
{
	return m_rect->getRotation();
}

void Cell::setPos(Vector2f newPos)
{
	m_newPos = newPos;
}

void Cell::setSize(Vector2f newSize)
{
	m_data->size = newSize;
	m_rect->setScale(newSize);
}

RectangleShape& Cell::getRectangleShape()
{
	return m_rect->getRectangleShape();
}