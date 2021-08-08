#pragma once
#include <SFML/Graphics.hpp>

#include "../../Support.h"

using namespace sf;

struct FoodData
{
	Color color = Color::Yellow;
	Vector2f pos = { 50, 50 };
	Vector2f size;
};

class Food
{
private:
	std::shared_ptr<RenderWindow> m_window;
	std::unique_ptr<FoodData> m_data;
	RectangleShape m_rect;

public:
	Food(std::shared_ptr<RenderWindow>, std::unique_ptr<FoodData>);
	~Food();

	void processEvent();
	void processLogic(float time);
	void processDraw();

	void setPos(Vector2f);

	RectangleShape& getRectangleShape();
};
