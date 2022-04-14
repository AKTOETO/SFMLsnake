#include "StaticPicture.h"
namespace Engine
{
	template<class T>
	void StaticPicture::addData(std::unique_ptr<T>& data)
	{
		ERROR("incorrect type of data")
	}
	
	template<>
	void StaticPicture::addData<SpriteData>(std::unique_ptr<SpriteData>& data)
	{
		INFO("\t\t\tpic add info")
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
			Engine::SupportFunc::loadTexture(m_texture, file);


		INFO("\t\t\tsetting up the st. picture")
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
	void StaticPicture::addData<ShapeData>(std::unique_ptr<ShapeData>& data)
	{
		INFO("\t\tshape add info")
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

	StaticPicture::StaticPicture()
	{

	};

	StaticPicture::StaticPicture(std::shared_ptr<Engine::Context> context)
		:BaseObject(context),
		m_shapeData(nullptr),
		m_circle(nullptr),
		m_rectangle(nullptr),
		m_sprite(nullptr),
		m_spriteData(nullptr),
		m_texture(nullptr)
	{
		INFO("\t\t\tnull stat. pic. const.")
	}

	StaticPicture::StaticPicture(const StaticPicture& pic)
	{
		INFO("\t\t\tstat. pic. copy const.")
#define NOTNULLCOPY(mem, obj) if(pic.mem != nullptr) mem = std::make_unique<obj>(*pic.mem);
		NOTNULLCOPY(m_circle, CircleShape)
		NOTNULLCOPY(m_rectangle, RectangleShape)
		NOTNULLCOPY(m_shapeData, ShapeData)
		NOTNULLCOPY(m_sprite, Sprite)
		NOTNULLCOPY(m_spriteData, SpriteData)
		NOTNULLCOPY(m_texture, Texture)
	}

	StaticPicture::StaticPicture(StaticPicture&& pic) noexcept
	{
		INFO("\t\t\tstat. pic. move const.")
#define MOVE(mem) mem = std::move(pic.mem);
			MOVE(m_circle)
			MOVE(m_rectangle)
			MOVE(m_shapeData)
			MOVE(m_sprite)
			MOVE(m_spriteData)
			MOVE(m_texture)
	}

	StaticPicture& StaticPicture::operator=(StaticPicture&& pic) noexcept
	{
		if (this != &pic)
		{
			NOTNULLCOPY(m_circle, CircleShape)
			NOTNULLCOPY(m_rectangle, RectangleShape)
			NOTNULLCOPY(m_shapeData, ShapeData)
			NOTNULLCOPY(m_sprite, Sprite)
			NOTNULLCOPY(m_spriteData, SpriteData)
			NOTNULLCOPY(m_texture, Texture)

			pic.destruct();
		}
		return *this;
	}

	StaticPicture::StaticPicture(std::shared_ptr<Engine::Context> context, std::unique_ptr<SpriteData>& data)
		:BaseObject(context), m_shapeData(nullptr), m_rectangle(nullptr), m_circle(nullptr)
	{
		INFO("\t\t\tstat. pic. const. START")
			addData<SpriteData>(data);
		INFO("\t\t\tstat. pic. const. END")
	}

	StaticPicture::StaticPicture(std::shared_ptr<Engine::Context> context, std::unique_ptr<ShapeData>& data)
		:BaseObject(context), m_spriteData(nullptr), m_sprite(nullptr), m_texture(nullptr)
	{
		addData<ShapeData>(data);
	}

	StaticPicture::~StaticPicture()
	{
		destruct();
		INFO("\t\t\tst. pic. destructor")
	}

	void StaticPicture::destruct()
	{
		m_circle.reset(nullptr);
		m_rectangle.reset(nullptr);

		m_shapeData.reset(nullptr);
		m_spriteData.reset(nullptr);

		m_sprite.reset(nullptr);

		//m_texture.reset(nullptr);
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

	void StaticPicture::draw(RenderTarget& target, RenderStates states) const
	{
		IF_SPRITE target.draw(*m_sprite, states);
		EIF_RECT target.draw(*m_rectangle, states);
		EIF_CIRC target.draw(*m_circle, states);
	}
}