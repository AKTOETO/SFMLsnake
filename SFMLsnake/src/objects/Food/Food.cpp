#include "Food.h"

Food::Food(std::shared_ptr<Engine::Context> context, std::unique_ptr<FoodData> data)
	:BaseObject(context)
{
	INFO("food constructor")
	m_data = std::move(data);

	//collision shape
	std::unique_ptr<Engine::ShapeData> shData(new Engine::ShapeData);
	shData->size = Vector2f(15, 15);
	shData->position = m_data->pos;
	shData->type = Engine::ShapeType::RECTANGLE;

	m_collisRect = std::make_unique<Engine::StaticPicture>(m_context, shData);

	//animated picture
	std::unique_ptr<Engine::AnimationData> aData(new Engine::AnimationData);
	aData->type = Engine::AnimationType::LOOP;
	aData->numberOfFrame = 4;
	aData->data.borders = IntRect(1, 1, 40, 40);
	aData->data.position = Vector2f(m_data->pos);
	std::shared_ptr<Texture> texture(new Texture);
	Engine::SupportFunc::loadTexture(texture, "food.png");
	aData->data.texture = texture;
	aData->data.type = Engine::SpriteType::NONE;

	std::unique_ptr<Engine::AnimatedPicture> animStay(new Engine::AnimatedPicture(m_context, aData));

	m_animManager = std::make_unique<Engine::AnimationManager>();
	m_animManager->addAnim(Engine::AnimType::STAY, animStay);
	m_animManager->useAnim(Engine::AnimType::STAY);
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

void Food::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(*m_animManager);
	if(SHB) target.draw(*m_collisRect);
}

void Food::setPos(Vector2f pos)
{
	m_collisRect->setPosition(pos);
	m_animManager->getAnimation(Engine::AnimType::STAY)->setPosition(pos);
}

RectangleShape& Food::getRectangleShape()
{
	return m_collisRect->getRectangleShape();
}