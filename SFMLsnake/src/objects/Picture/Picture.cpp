#include "Picture.h"

Picture::Picture(std::unique_ptr<SpriteData> data)
	:m_shapeData(nullptr), m_rectangle(nullptr), m_circle(nullptr)
{
	m_spriteData = std::move(data);

	//create sprite, texture
	m_sprite = std::make_unique<Sprite>();
	m_texture = std::make_unique<Texture>();

	//choose file texture
	std::string file;
	switch (m_spriteData->type)
	{
	case SNAKE:
		file = "snake.png";
		break;
	case FOOD:
		file = "food.png";
		break;
	}

	//load texture
	if (!m_texture->loadFromFile("assets/textures/" + file))
		std::cout << "failed to load " << file << " (wrong path) <Picture.cpp>\n";

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

Picture::Picture(std::unique_ptr<ShapeData> data)
	:m_spriteData(nullptr), m_sprite(nullptr), m_texture(nullptr)
{
	m_shapeData = std::move(data);

	switch (m_shapeData->type)
	{
	case RECTANGLE:
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
	case CIRCLE:
		//...
		break;
	}
}

Picture::~Picture()
{
}

void Picture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_sprite != nullptr)
	{
		target.draw(*m_sprite, states);
	}
	else if (m_shapeData->type == ShapeType::RECTANGLE && m_rectangle != nullptr)
	{
		target.draw(*m_rectangle, states);
	}
	else if (m_shapeData->type == ShapeType::CIRCLE && m_circle != nullptr)
	{
		target.draw(*m_circle, states);
	}
}

template<>
inline void Picture::addData(std::unique_ptr<SpriteData> data) const
{
	//...
}

template<>
inline void Picture::addData(std::unique_ptr<ShapeData> data) const
{
	//...
}

