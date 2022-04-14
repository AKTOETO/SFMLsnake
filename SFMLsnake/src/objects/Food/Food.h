#pragma once
#include <SFML/Graphics.hpp>

#include "../../Engine/managers/AnimationManager/AnimationManager.h"
#include "../../Engine/objects/BaseObject.h"

struct FoodData
{
	Color color = Color::Yellow;
	Vector2f pos = { 50, 50 };
	Vector2f size;
};

class Food : public Engine::BaseObject
{
private:
	std::unique_ptr<FoodData> m_data;

	std::unique_ptr<Engine::StaticPicture> m_collisRect;
	std::unique_ptr<Engine::AnimationManager> m_animManager;

public:
	Food(std::shared_ptr<Engine::Context>, std::unique_ptr<FoodData>);
	~Food();

	void processEvent() override;
	int processLogic(float time) override;
	void draw(RenderTarget& target, RenderStates states) const override;

	void setPos(Vector2f);

	RectangleShape& getRectangleShape();
};
