#include "Picture.h"

Picture::Picture(std::unique_ptr<SpriteData> data)
	:m_shapeData(nullptr)
{
	m_spriteData = std::move(data);

	//create sprite
	m_sprite = std::make_unique<Sprite>();

	//create texture
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

	//bind texture to sprite and setting it
	m_sprite->setTexture(*m_texture);
	m_sprite->setPosition(m_spriteData->position);
	m_sprite->setTextureRect(m_spriteData->borders);
	m_sprite->setScale(m_spriteData->size);

	//origin in center
	if (m_spriteData->originInCenter == true)
		m_sprite->setOrigin(
			m_sprite->getLocalBounds().width / 2,
			m_sprite->getLocalBounds().height / 2
		);
}

//Picture::Picture(std::shared_ptr<RenderWindow>, ShapeData)
//{
//}

Picture::~Picture()
{
}

void Picture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_sprite != nullptr)
	{
		target.draw(*m_sprite, states);
	}
	//else if(m_shape)
}
