#pragma once
#include <SFML/Graphics.hpp>

#include "AnimationManager/AnimationManager.h"
#include "BaseObject.h"

using namespace sf;

struct FoodData
{
	Color color = Color::Yellow;
	Vector2f pos = { 50, 50 };
	Vector2f size;
};

class Food : public BaseObject
{
private:
	std::unique_ptr<FoodData> m_data;

	std::unique_ptr<StaticPicture> m_collisRect;
	std::unique_ptr<AnimationManager> m_animManager;

public:
	Food(std::shared_ptr<RenderWindow>, std::unique_ptr<FoodData>);
	~Food();

	virtual void processEvent() override;
	virtual int processLogic(float time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPos(Vector2f);

	RectangleShape& getRectangleShape();
};
