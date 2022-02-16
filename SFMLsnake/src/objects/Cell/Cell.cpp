#include "Cell.h"

Cell::Cell(std::unique_ptr<CellData> data)
	:m_rect(new Engine::StaticPicture)
{
	//INFO("\tcell constructor")

		m_data = move(data);

	// ===== RECT DATA & RECT OBJECT =====
	//INFO("\trect data")
		std::unique_ptr<Engine::ShapeData> shData(new Engine::ShapeData);
	shData->size = m_data->size;
	shData->position = m_data->pos;
	shData->color = m_data->color;
	shData->angle = m_data->rotation;

	m_rect->addData<Engine::ShapeData>(shData);
	// =====================

	//===== LOAD TEXTURE =====
	//INFO("\tload texture")
	std::shared_ptr<Texture> texture(new Texture);
	Engine::SupportFunc::loadTexture(texture, "snake.png");
	// ===================

	// ===== MOVE ANIMATION DATA =====
	//INFO("\tmove anim data")
		std::unique_ptr<Engine::AnimationData> animDataMove(new Engine::AnimationData);
	animDataMove->offset = Engine::TextureOffset::RIGHT;
	animDataMove->numberOfFrame = 4;
	animDataMove->data.position = { m_rect->getPosition() };
	animDataMove->data.texture = texture;
	animDataMove->data.type = Engine::SpriteType::NONE;
	animDataMove->data.size = Vector2f(1, 1);

	//animDataMove->animSpeed = 0.0005;
	// ==================

	// ===== DIE ANIMATION DATA =====
	//INFO("\tdie anim data")
		std::unique_ptr<Engine::AnimationData> animDataDie(new Engine::AnimationData);
	animDataDie->offset = Engine::TextureOffset::RIGHT;
	animDataDie->numberOfFrame = 7;
	animDataDie->data.position = { m_rect->getPosition() };
	animDataDie->type = Engine::AnimationType::ONCE;
	animDataDie->data.texture = texture;
	animDataDie->data.type = Engine::SpriteType::NONE;
	animDataDie->data.size = Vector2f(1, 1);

	//animDataDie->animSpeed = 0.0005;
	// ==================

	//==========HEAD==========
	if (m_data->head == true)
	{
#define POSG(param) m_rect->getPosition().param

		m_collisionPoint = std::make_unique<Vector2f>(POSG(x), POSG(y) - m_data->size.y / 2);
		animDataMove->data.borders = { 1, 1, 40, 40 }; //{ 1, 83, 40, 40 };
		animDataDie->data.borders = { 165, 1, 40, 40 }; //{ 165, 83, 40 ,40 };
	}
	else
	{
		//==========BODY==========
		animDataMove->data.borders = { 1, 42, 40, 40 }; //{ 1, 124, 40, 40 }; 
		animDataDie->data.borders = { 165, 42, 40, 40 }; //{ 165, 124, 40, 40 }; 
	}
	m_posBackPoint = std::make_unique<Vector2f>(
		sin(-m_rect->getRotation()) * m_data->size.x / 2 + POSG(x),
		cos(-m_rect->getRotation()) * m_data->size.y / 2 + POSG(y)
		);
	m_posFrontPoint = std::make_unique<Vector2f>(
		-sin(-m_rect->getRotation()) * m_data->size.x / 2 + POSG(x),
		-cos(-m_rect->getRotation()) * m_data->size.y / 2 + POSG(y)
		);


	// ===== ANIMATIONS =====
	//INFO("\tcreate anim")
	std::unique_ptr<Engine::AnimatedPicture> animMove(new Engine::AnimatedPicture(animDataMove));
	std::unique_ptr<Engine::AnimatedPicture> animDie(new Engine::AnimatedPicture(animDataDie));
	//INFO("\tanim created")
		// ===================


		// ===== ANIM MANAGER DATA =====
		//INFO("\tanim manager add sc. & use sc.")
	m_animManager = std::make_unique<Engine::AnimationManager>();
	m_animManager->addAnim(Engine::AnimType::MOVE, animMove);
	m_animManager->addAnim(Engine::AnimType::DIE, animDie);
	m_animManager->useAnim(Engine::AnimType::MOVE);
	// ===================
}

Cell::~Cell()
{
	//INFO("destructor")
	m_data.reset(nullptr);

	m_collisionPoint.reset(nullptr);
	m_posBackPoint.reset(nullptr);
	m_posFrontPoint.reset(nullptr);

	//m_sprite.reset(nullptr);
	m_rect.reset(nullptr);
}

void Cell::processEvent()
{
#define PRESS(param) Keyboard::isKeyPressed(Keyboard::param)
	if (m_data->head == true && (PRESS(A) || PRESS(Left)) && m_dir != Engine::Direction::RIGHT)
		m_dir = Engine::Direction::LEFT;
	else if (m_data->head == true && (PRESS(W) || PRESS(Up)) && m_dir != Engine::Direction::DOWN)
		m_dir = Engine::Direction::UP;
	else if (m_data->head == true && (PRESS(D) || PRESS(Right)) && m_dir != Engine::Direction::LEFT)
		m_dir = Engine::Direction::RIGHT;
	else if (m_data->head == true && (PRESS(S) || PRESS(Down)) && m_dir != Engine::Direction::UP)
		m_dir = Engine::Direction::DOWN;
}

int Cell::processLogic(float time)
{

#define POSFG(param) m_posFrontPoint->param
	//==========HEAD==========
	if (m_data->head == true)
	{
#define POSG(param) m_rect->getPosition().param
#define BOUND(param) float(m_rect->getRectangleShape().getSize().param)
		//collision with wall
		if (
			POSG(x) + BOUND(x) / 2 > W_WIDTH ||
			POSG(y) + BOUND(y) / 2 > W_HEIGHT ||
			POSG(x) - BOUND(x) / 2 < 0 ||
			POSG(y) - BOUND(y) / 2 < 0
			)
		{
			m_dir = Engine::Direction::STOP;
			m_animManager->useAnim(Engine::AnimType::DIE);
			//INFO("wall collision");
		}

		//head mooving
		if (m_dir == Engine::Direction::LEFT)
		{
			if (POSG(x) - BOUND(x) / 2 > 0)
			{
				m_rect->setPosition(Vector2f(POSG(x) - SPEED * time, POSG(y)));
			}
			else
			{
				m_rect->setPosition({ BOUND(x) / 2, POSG(y) });
			}

			m_animManager->getAnimation(Engine::AnimType::MOVE)->setRotation(270);
			m_rect->setRotation(270);
		}
		else if (m_dir == Engine::Direction::RIGHT)
		{
			if (POSG(x) + BOUND(x) / 2 < W_WIDTH)
			{
				m_rect->setPosition(Vector2f(POSG(x) + SPEED * time, POSG(y)));
			}
			else
			{
				m_rect->setPosition({ W_WIDTH - BOUND(x) / 2, POSG(y) });
			}

			m_animManager->getAnimation(Engine::AnimType::MOVE)->setRotation(90);
			m_rect->setRotation(90);
		}
		else if (m_dir == Engine::Direction::UP)
		{
			if (POSG(y) - BOUND(x) / 2 > 0)
			{
				m_rect->setPosition(Vector2f(POSG(x), POSG(y) - SPEED * time));
			}
			else
			{
				m_rect->setPosition({ POSG(x), BOUND(x) / 2 });
			}

			m_animManager->getAnimation(Engine::AnimType::MOVE)->setRotation(0);
			m_rect->setRotation(0);
		}
		else if (m_dir == Engine::Direction::DOWN)
		{
			if (POSG(y) + BOUND(x) / 2 < W_HEIGHT)
			{
				m_rect->setPosition(Vector2f(POSG(x), POSG(y) + SPEED * time));
			}
			else
			{
				m_rect->setPosition({ POSG(x), W_HEIGHT - BOUND(x) / 2 });
			}

			m_animManager->getAnimation(Engine::AnimType::MOVE)->setRotation(180);
			m_rect->setRotation(180);
		}

		//collision rectangle logic
		switch (m_dir)
		{
		case Engine::Direction::UP:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x), POSG(y) - BOUND(y) / 2));
			break;
		case Engine::Direction::DOWN:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x), POSG(y) + BOUND(y) / 2));
			break;
		case Engine::Direction::LEFT:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x) - BOUND(y) / 2, POSG(y)));
			break;
		case Engine::Direction::RIGHT:
			m_collisionPoint = std::make_unique<Vector2f>(Vector2f(POSG(x) + BOUND(y) / 2, POSG(y)));
			break;
		}
	}
	//==========BODY==========
	else
	{
		if (m_dir != Engine::Direction::STOP)
		{
			float k = 0.06; // smoothness of movement //0.1

			m_rect->setPosition(Vector2f(
				POSG(x) + ((m_newPos.x - POSFG(x)) * SPEED * time * k),
				POSG(y) + ((m_newPos.y - POSFG(y)) * SPEED * time * k)
			));

			m_deltaX = (m_newPos.x - POSG(x));
			m_deltaY = (m_newPos.y - POSG(y));

			if ((m_newPos.x - POSG(x) <= 0 and m_newPos.y - POSG(y) >= 0) or
				(m_newPos.x - POSG(x) >= 0 and m_newPos.y - POSG(y) >= 0))
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

			m_rotation = m_rect->getRotation();

			//temp
			m_animManager->getAnimation(Engine::AnimType::MOVE)->setRotation(m_rect->getRotation());
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

	m_animManager->getAnimation(Engine::AnimType::MOVE)->setPosition(m_rect->getPosition());
	
	if (m_animManager->processLogic(time) == 1)
	{
		m_wallCollision = true;
	}

	return 0;
}

void Cell::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(*m_animManager);
	if (SHB)target.draw(*m_rect);
}

Vector2f Cell::getCollisionPoint()
{
	return *m_collisionPoint;
}

Vector2f Cell::getSize() const
{
	return m_data->size;
}

Vector2f Cell::getBackPos() const
{
	return *m_posBackPoint;
}

Vector2f Cell::getCenterPos() const
{
	return m_rect->getPosition();
}

Vector2f Cell::getFrontPos() const
{
	return *m_posFrontPoint;
}

void Cell::setDirection(Engine::Direction dir)
{
	//body die
	if (m_dir != Engine::Direction::STOP && dir == Engine::Direction::STOP)
		m_animManager->useAnim(Engine::AnimType::DIE);
	m_dir = dir;
}

void Cell::setRotation(float rotation)
{
	m_rect->setRotation(rotation);
}

Engine::Direction Cell::getDirection() const
{
	return m_dir;
}

float Cell::getRotation() const
{
	return m_rect->getRotation();
}

float Cell::getDeltaX() const
{
	return m_deltaX;
}

float Cell::getDeltaY() const
{
	return m_deltaY;
}

bool Cell::getWallCollision() const
{
	return m_wallCollision;
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