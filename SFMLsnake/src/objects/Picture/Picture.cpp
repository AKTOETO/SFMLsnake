#include "Picture.h"

template<>
void StaticPicture::addData(std::unique_ptr<SpriteData>& data)
{
	m_spriteData = std::move(data);

	//create sprite, texture
	m_sprite = std::make_unique<Sprite>();
	m_texture = std::make_unique<Texture>();

	//choose file texture
	std::string file;
	switch (m_spriteData->type)
	{
	case SpriteType::NONE:
		file = "none";
		break;
	case SpriteType::SNAKE:
		file = "snake.png";
		break;
	case SpriteType::FOOD:
		file = "food.png";
		break;
	}

	//load texture
	if (file == "none")
	{
		m_texture = std::make_shared<Texture>();
		m_texture = m_spriteData->texture;
	}
	else
		loadTexture(m_texture, file);


	//bind texture to sprite and setting
	m_sprite->setTexture(*m_texture);
	m_sprite->setPosition(m_spriteData->position);
	m_sprite->setTextureRect(m_spriteData->borders);
	m_sprite->setScale(m_spriteData->size);
	m_sprite->setRotation(m_spriteData->angle);

	//origin in center
	if (m_spriteData->originInCenter == true)
		m_sprite->setOrigin(
			m_sprite->getLocalBounds().width / 2,
			m_sprite->getLocalBounds().height / 2
		);
}

template<>
void StaticPicture::addData(std::unique_ptr<ShapeData>& data)
{
	m_shapeData = std::move(data);

	switch (m_shapeData->type)
	{
	case ShapeType::RECTANGLE:
		m_rectangle = std::make_unique<RectangleShape>();
		m_rectangle->setSize(m_shapeData->size);
		if (m_shapeData->originInCenter)
			m_rectangle->setOrigin(
				m_rectangle->getLocalBounds().width / 2,
				m_rectangle->getLocalBounds().height / 2
			);
		m_rectangle->setPosition(m_shapeData->position);
		m_rectangle->setFillColor(m_shapeData->color);
		m_rectangle->setRotation(m_shapeData->angle);
		break;
	case ShapeType::CIRCLE:
		//...
		INFO("circle setting")
			break;
	}
}

template<typename T>
inline void StaticPicture::addData(std::unique_ptr<T>& data)
{
	ERROR("incorrect type of data")
}

StaticPicture::StaticPicture()
	:m_shapeData(nullptr),
	m_circle(nullptr),
	m_rectangle(nullptr),
	m_sprite(nullptr),
	m_spriteData(nullptr),
	m_texture(nullptr)
{
}

StaticPicture::StaticPicture(const StaticPicture& pic)
{
#define NOTNULLCOPY(mem, obj) if(pic.mem != nullptr) mem = std::make_unique<obj>(*pic.mem);
	NOTNULLCOPY(m_circle, CircleShape)
	NOTNULLCOPY(m_rectangle, RectangleShape)
	NOTNULLCOPY(m_shapeData, ShapeData)
	NOTNULLCOPY(m_sprite, Sprite)
	NOTNULLCOPY(m_spriteData, SpriteData)
	NOTNULLCOPY(m_texture, Texture)
}

StaticPicture::StaticPicture(std::unique_ptr<SpriteData>& data)
	: m_shapeData(nullptr), m_rectangle(nullptr), m_circle(nullptr)
{
	addData<SpriteData>(data);
}

StaticPicture::StaticPicture(std::unique_ptr<ShapeData>& data)
	: m_spriteData(nullptr), m_sprite(nullptr), m_texture(nullptr)
{
	addData<ShapeData>(data);
}

StaticPicture::~StaticPicture()
{
	m_circle.reset(nullptr);
	m_rectangle.reset(nullptr);

	m_shapeData.reset(nullptr);
	m_spriteData.reset(nullptr);

	m_sprite.reset(nullptr);
	//m_texture.reset(nullptr);
	INFO("destructor StaticPicture")
}

//choose sprite or rectangle or circle
#define IF_SPRITE if (m_sprite != nullptr)
#define EIF_RECT else if (m_shapeData->type == ShapeType::RECTANGLE && m_rectangle != nullptr)
#define EIF_CIRC else if (m_shapeData->type == ShapeType::CIRCLE && m_circle != nullptr)

void StaticPicture::setPosition(Vector2f pos)
{
	IF_SPRITE m_sprite->setPosition(pos);
	EIF_RECT m_rectangle->setPosition(pos);
	EIF_CIRC m_circle->setPosition(pos);
}

void StaticPicture::setRotation(float angle)
{
	IF_SPRITE m_sprite->setRotation(angle);
	EIF_RECT m_rectangle->setRotation(angle);
	EIF_CIRC m_circle->setRotation(angle);
}

void StaticPicture::setScale(Vector2f size)
{
	IF_SPRITE m_sprite->setScale(size);
	EIF_RECT m_rectangle->setScale(size);
	EIF_CIRC m_circle->setScale(size);
}

Vector2f StaticPicture::getPosition() const
{
	IF_SPRITE return m_sprite->getPosition();
	EIF_RECT return m_rectangle->getPosition();
	EIF_CIRC return m_circle->getPosition();
}

float StaticPicture::getRotation() const
{
	IF_SPRITE return m_sprite->getRotation();
	EIF_RECT return m_rectangle->getRotation();
	EIF_CIRC return m_circle->getRotation();
}

Vector2f StaticPicture::getScale() const
{
	IF_SPRITE return m_sprite->getScale();
	EIF_RECT return m_rectangle->getScale();
	EIF_CIRC return m_circle->getScale();
}

RectangleShape& StaticPicture::getRectangleShape() const
{
	return *m_rectangle;
}

void StaticPicture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	IF_SPRITE target.draw(*m_sprite, states);
	EIF_RECT target.draw(*m_rectangle, states);
	EIF_CIRC target.draw(*m_circle, states);
}