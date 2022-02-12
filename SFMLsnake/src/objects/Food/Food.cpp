#include "Food.h"

Food::Food(std::shared_ptr<RenderWindow> window, std::unique_ptr<FoodData> data)
{
	INFO("food constructor")
	m_data = std::move(data);

	//collision shape
	std::unique_ptr<ShapeData> shData(new ShapeData);
	shData->size = Vector2f(15, 15);
	shData->position = m_data->pos;
	shData->type = ShapeType::RECTANGLE;

	m_collisRect = std::make_unique<StaticPicture>(shData);

	//animated picture
	std::unique_ptr<AnimationData> aData(new AnimationData);
	aData->type = AnimationType::LOOP;
	aData->numberOfFrame = 4;
	aData->data.borders = IntRect(1, 1, 40, 40);
	aData->data.position = Vector2f(m_data->pos);
	std::shared_ptr<Texture> texture(new Texture);
	loadTexture(texture, "food.png");
	aData->data.texture = texture;
	aData->data.type = SpriteType::NONE;

	std::unique_ptr<AnimatedPicture> animStay(new AnimatedPicture(aData));

	m_animManager = std::make_unique<AnimationManager>();
	m_animManager->addAnim(AnimType::STAY, animStay);
	m_animManager->useAnim(AnimType::STAY);
}

Food::~Food()
{
	INFO("food destructor")
}

void Food::processEvent()
{
}

int Food::processLogic(float time)
{
	m_animManager->processLogic(time);
	return 0;
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_animManager);
	if(SHB) target.draw(*m_collisRect);
}

void Food::setPos(Vector2f pos)
{
	m_collisRect->setPosition(pos);
	m_animManager->getAnimation(AnimType::STAY)->setPosition(pos);
}

RectangleShape& Food::getRectangleShape()
{
	return m_collisRect->getRectangleShape();
}