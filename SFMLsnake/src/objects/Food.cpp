#include "Food.h"

Food::Food(std::shared_ptr<RenderWindow> window, std::unique_ptr<FoodData> data)
	:m_window(window)
{
	m_data = std::move(data);

	//collision shape
	std::unique_ptr<ShapeData> shData(new ShapeData);
	shData->size = Vector2f(15, 15);
	shData->position = m_data->pos;
	shData->type = ShapeType::RECTANGLE;

	m_collisRect = std::make_unique<StaticPicture>(shData);

	//animated picture
	std::unique_ptr<AnimationData> aData(new AnimationData);
	aData->animType = AnimationType::FOODSTAY;
	aData->numberOfFrame = 4;
	aData->data.borders = IntRect(1, 1, 40, 40);
	aData->data.position = Vector2f(m_data->pos);
	std::shared_ptr<Texture> texture(new Texture);
	loadTexture(texture, "food.png");
	aData->data.texture = texture;
	aData->data.type = SpriteType::NONE;

	m_animSprite = std::make_unique<AnimatedPicture>(aData);
}

Food::~Food()
{
}

void Food::processEvent()
{
}

void Food::processLogic(float time)
{
	m_animSprite->processLogic(time);
}

void Food::processDraw()
{
	m_window->draw(*m_animSprite);
	if(SHB)
		m_window->draw(*m_collisRect);
}

void Food::setPos(Vector2f pos)
{
	m_collisRect->setPosition(pos);
	m_animSprite->setPosition(pos);
}

RectangleShape& Food::getRectangleShape()
{
	return m_collisRect->getRectangleShape();
}